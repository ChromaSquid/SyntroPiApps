//
//  Copyright (c) 2014 richards-tech.
//
//  This file is part of SyntroNet
//
//  SyntroNet is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  SyntroNet is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with SyntroNet.  If not, see <http://www.gnu.org/licenses/>.
//

#include "SelectIMUDlg.h"
#include "RTIMUSettings.h"
#include "IMUDrivers/RTIMUMPU9150.h"
#include "IMUDrivers/RTIMUMPU9250.h"
#include "IMUDrivers/RTIMUGD20HM303D.h"
#include "IMUDrivers/RTIMUGD20M303DLHC.h"
#include "IMUDrivers/RTIMULSM9DS0.h"

#include <QFormLayout>
#include <QLabel>

SelectIMUDlg::SelectIMUDlg(RTIMUSettings *settings, QWidget *parent)
    : QDialog(parent, Qt::WindowCloseButtonHint | Qt::WindowTitleHint)
{
    m_settings = settings;
    layoutWindow();
    setWindowTitle("Select IMU");
    connect(m_buttons, SIGNAL(accepted()), this, SLOT(onOk()));
    connect(m_buttons, SIGNAL(rejected()), this, SLOT(onCancel()));
    connect(m_selectIMU, SIGNAL(currentIndexChanged(int)), this, SLOT(setSelectAddress(int)));
    connect(m_selectBus, SIGNAL(currentIndexChanged(int)), this, SLOT(setSelectAddress(int)));
}

SelectIMUDlg::~SelectIMUDlg()
{
}

void SelectIMUDlg::onOk()
{
    if (m_selectBus->currentIndex() < 8) {
        // I2C
        m_settings->m_busIsI2C = true;
        m_settings->m_I2CBus = m_selectBus->currentIndex();
        m_settings->m_I2CSlaveAddress = m_selectAddress->itemData(m_selectAddress->currentIndex()).toInt();
    } else {
        // SPI
        m_settings->m_busIsI2C = false;
        m_settings->m_SPIBus = m_selectBus->currentIndex() - 8;
    }
    m_settings->m_imuType = m_selectIMU->currentIndex();
    m_settings->saveSettings();

    accept();
}

void SelectIMUDlg::onCancel()
{
    reject();
}

void SelectIMUDlg::layoutWindow()
{
    QVBoxLayout *mainLayout;
    QFormLayout *form;

    setModal(true);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(11, 11, 11, 11);

    form = new QFormLayout();
    mainLayout->addLayout(form);

    m_selectBus = new QComboBox();
    m_selectBus->addItem("I2C bus 0");
    m_selectBus->addItem("I2C bus 1");
    m_selectBus->addItem("I2C bus 2");
    m_selectBus->addItem("I2C bus 3");
    m_selectBus->addItem("I2C bus 4");
    m_selectBus->addItem("I2C bus 5");
    m_selectBus->addItem("I2C bus 6");
    m_selectBus->addItem("I2C bus 7");
    m_selectBus->addItem("SPI bus 0");
    m_selectBus->addItem("SPI bus 1");
    m_selectBus->addItem("SPI bus 2");
    m_selectBus->addItem("SPI bus 3");
    m_selectBus->addItem("SPI bus 4");
    m_selectBus->addItem("SPI bus 5");
    m_selectBus->addItem("SPI bus 6");
    m_selectBus->addItem("SPI bus 7");

    if (m_settings->m_busIsI2C)
        m_selectBus->setCurrentIndex(m_settings->m_I2CBus);
    else
        m_selectBus->setCurrentIndex(m_settings->m_SPIBus + 8);

    form->addRow("select bus type: ", m_selectBus);

    m_selectIMU = new QComboBox();

    m_selectIMU->addItem("Auto detect IMU");
    m_selectIMU->addItem("Null IMU");
    m_selectIMU->addItem("InvenSense MPU9150");
    m_selectIMU->addItem("STM L3GD20H/LSM303D");
    m_selectIMU->addItem("STM L3GD20/LSM303DLHC");
    m_selectIMU->addItem("STM LSM9DS0");
    m_selectIMU->addItem("InvenSense MPU9250");

    m_selectIMU->setCurrentIndex(m_settings->m_imuType);

    form->addRow("select IMU type: ", m_selectIMU);

    m_selectAddress = new QComboBox();
    setSelectAddress(m_settings->m_imuType, m_settings->m_I2CSlaveAddress);

    form->addRow("select I2C address type: ", m_selectAddress);

    m_buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    m_buttons->setCenterButtons(true);

    mainLayout->addWidget(m_buttons);
}

void SelectIMUDlg::setSelectAddress(int)
{
    int imuType = m_selectIMU->currentIndex();
    if (imuType == m_settings->m_imuType)
        setSelectAddress(imuType, m_settings->m_I2CSlaveAddress);
    else
        setSelectAddress(imuType, -1);
}

void SelectIMUDlg::setSelectAddress(int imuType, int slaveAddress)
{
    m_selectAddress->clear();

    if (m_selectBus->currentIndex() < 8) {
        switch (imuType) {
        case RTIMU_TYPE_MPU9150:
            m_selectAddress->addItem("Standard (0x68)", MPU9150_ADDRESS0);
            m_selectAddress->addItem("Option (0x69)", MPU9150_ADDRESS1);
            if (slaveAddress == MPU9150_ADDRESS1)
                m_selectAddress->setCurrentIndex(1);
            else
                m_selectAddress->setCurrentIndex(0);
            break;

        case RTIMU_TYPE_MPU9250:
            m_selectAddress->addItem("Standard (0x68)", MPU9250_ADDRESS0);
            m_selectAddress->addItem("Option (0x69)", MPU9250_ADDRESS1);
            if (slaveAddress == MPU9250_ADDRESS1)
                m_selectAddress->setCurrentIndex(1);
            else
                m_selectAddress->setCurrentIndex(0);
            break;

        case RTIMU_TYPE_GD20HM303D:
            m_selectAddress->addItem("Standard (0x6a)", L3GD20H_ADDRESS0);
            m_selectAddress->addItem("Option (0x6b)", L3GD20H_ADDRESS1);
            if (slaveAddress == L3GD20H_ADDRESS1)
                m_selectAddress->setCurrentIndex(1);
            else
                m_selectAddress->setCurrentIndex(0);
            break;

        case RTIMU_TYPE_GD20M303DLHC:
            m_selectAddress->addItem("Standard (0x6a)", L3GD20_ADDRESS0);
            m_selectAddress->addItem("Option (0x6b)", L3GD20_ADDRESS1);
            if (slaveAddress == L3GD20_ADDRESS1)
                m_selectAddress->setCurrentIndex(1);
            else
                m_selectAddress->setCurrentIndex(0);
            break;

        case RTIMU_TYPE_LSM9DS0:
            m_selectAddress->addItem("Standard (0x6a)", LSM9DS0_GYRO_ADDRESS0);
            m_selectAddress->addItem("Option (0x6b)", LSM9DS0_GYRO_ADDRESS1);
            if (slaveAddress == LSM9DS0_GYRO_ADDRESS1)
                m_selectAddress->setCurrentIndex(1);
            else
                m_selectAddress->setCurrentIndex(0);
            break;

        default:
            m_selectAddress->addItem("N/A", 0);
            break;
        }
    } else {
        switch (imuType) {
        case RTIMU_TYPE_MPU9250:
            m_selectAddress->addItem("Standard", MPU9250_ADDRESS0);
            m_selectAddress->setCurrentIndex(0);
            break;

        default:
            m_selectAddress->addItem("N/A", 0);
            break;
        }
    }
}

