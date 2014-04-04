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

#include "IMUThread.h"
#include "RTIMUMPU9150.h"
#include "RTKalman.h"
#include "SyntroPiNav.h"

IMUThread::IMUThread() : SyntroThread("IMUThread", "IMUThread")
{
    m_imu = NULL;
    m_calibrationMode = false;
    m_settings = new RTIMUSettings("RTIMULib");
}

IMUThread::~IMUThread()
{

}

void IMUThread::setCalibrationMode(bool enable)
{
    m_imu->setCalibrationMode(enable);
    m_calibrationMode = enable;
}

void IMUThread::newCompassCalData(const RTVector3& compassCalMin, const RTVector3& compassCalMax)
{
    m_settings->m_compassCalValid = true;
    m_settings->m_compassCalMin = compassCalMin;
    m_settings->m_compassCalMax = compassCalMax;
    m_settings->saveSettings();
    m_imu->setCalibrationData(true, compassCalMin, compassCalMax);
}


void IMUThread::initThread()
{
    m_imu = new RTIMUMPU9150(m_settings->m_kalmanType);

    //  set up IMU

    m_imu->IMUInit(m_settings);

    m_timer = startTimer(1000 / (2 * m_settings->m_MPU9150GyroAccelSampleRate));
}

void IMUThread::finishThread()
{
    killTimer(m_timer);

    if (m_imu != NULL)
        delete m_imu;

    m_imu = NULL;

    delete m_settings;
}

void IMUThread::timerEvent(QTimerEvent * /* event */)
{
    if (m_imu->IMURead()) {
        if (m_calibrationMode) {
            emit newCalData(m_imu->getCompass());
        } else {
            emit newIMUData(m_imu->getKalmanPose(), m_imu->getKalmanQPose(),
                            m_imu->getGyro(), m_imu->getAccel(), m_imu->getCompass(),
                            RTMath::currentUSecsSinceEpoch());
        }
    }
}
