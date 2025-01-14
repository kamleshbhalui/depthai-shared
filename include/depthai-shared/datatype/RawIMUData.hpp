#pragma once

#include "RawBuffer.hpp"
#include "depthai-shared/common/Point3f.hpp"
#include "depthai-shared/common/Timestamp.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

struct IMUReport {
    enum class Accuracy : std::uint8_t {
        UNRELIABLE = 0,
        LOW = 1,
        MEDIUM = 2,
        HIGH = 3,
    };
    /**
     * The sequence number increments once for each report sent.  Gaps
     * in the sequence numbers indicate missing or dropped reports.
     * Max value 255 after which resets to 0.
     */
    int32_t sequence = 0;

    /** Accuracy of sensor */
    Accuracy accuracy = Accuracy::UNRELIABLE;

    Timestamp timestamp = {};
};
DEPTHAI_SERIALIZE_EXT(IMUReport, sequence, accuracy, timestamp);

/**
 * @brief Accelerometer
 *
 * Units are [m/s^2]
 */
struct IMUReportAccelerometer : public IMUReport {
    float x = 0;
    float y = 0;
    float z = 0;
};
DEPTHAI_SERIALIZE_EXT(IMUReportAccelerometer, x, y, z, sequence, accuracy, timestamp);

/**
 * @brief Gyroscope
 *
 * Units are [rad/s]
 */
struct IMUReportGyroscope : public IMUReport {
    float x = 0;
    float y = 0;
    float z = 0;
};
DEPTHAI_SERIALIZE_EXT(IMUReportGyroscope, x, y, z, sequence, accuracy, timestamp);

/**
 * @brief Magnetic field
 *
 * Units are [uTesla]
 */
struct IMUReportMagneticField : public IMUReport {
    float x = 0;
    float y = 0;
    float z = 0;
};
DEPTHAI_SERIALIZE_EXT(IMUReportMagneticField, x, y, z, sequence, accuracy, timestamp);

/**
 * @brief Rotation Vector with Accuracy
 *
 * Contains quaternion components: i,j,k,real
 */
struct IMUReportRotationVectorWAcc : public IMUReport {
    float i = 0;                      /**< @brief Quaternion component i */
    float j = 0;                      /**< @brief Quaternion component j */
    float k = 0;                      /**< @brief Quaternion component k */
    float real = 0;                   /**< @brief Quaternion component, real */
    float rotationVectorAccuracy = 0; /**< @brief Accuracy estimate [radians], 0 means no estimate */
};
DEPTHAI_SERIALIZE_EXT(IMUReportRotationVectorWAcc, i, j, k, real, rotationVectorAccuracy, sequence, accuracy, timestamp);

#if 0

/**
 * @brief Uncalibrated gyroscope
 *
 * See the SH-2 Reference Manual for more detail.
 */
struct IMUReportGyroscopeUncalibrated : public IMUReport {
    /* Units are rad/s */
    float x = 0;     /**< @brief [rad/s] */
    float y = 0;     /**< @brief [rad/s] */
    float z = 0;     /**< @brief [rad/s] */
    float biasX = 0; /**< @brief [rad/s] */
    float biasY = 0; /**< @brief [rad/s] */
    float biasZ = 0; /**< @brief [rad/s] */
};
DEPTHAI_SERIALIZE_EXT(IMUReportGyroscopeUncalibrated, x, y, z, biasX, biasY, biasZ, sequence, accuracy, timestamp);



/**
 * @brief Uncalibrated magnetic field
 *
 * See the SH-2 Reference Manual for more detail.
 */
struct IMUReportMagneticFieldUncalibrated : public IMUReport {
    /* Units are uTesla */
    float x = 0;     /**< @brief [uTesla] */
    float y = 0;     /**< @brief [uTesla] */
    float z = 0;     /**< @brief [uTesla] */
    float biasX = 0; /**< @brief [uTesla] */
    float biasY = 0; /**< @brief [uTesla] */
    float biasZ = 0; /**< @brief [uTesla] */
};
DEPTHAI_SERIALIZE_EXT(IMUReportMagneticFieldUncalibrated, x, y, z, biasX, biasY, biasZ, sequence, accuracy, timestamp);



/**
 * @brief Rotation Vector
 *
 * See the SH-2 Reference Manual for more detail.
 */
struct IMUReportRotationVector : public IMUReport {
    float i = 0;    /**< @brief Quaternion component i */
    float j = 0;    /**< @brief Quaternion component j */
    float k = 0;    /**< @brief Quaternion component k */
    float real = 0; /**< @brief Quaternion component real */
};
DEPTHAI_SERIALIZE_EXT(IMUReportRotationVector, i, j, k, real, sequence, accuracy, timestamp);


/**
 * @brief Gyro integrated rotation vector
 *
 * See SH-2 Reference Manual for details.
 */
struct IMUReportGyroIntegratedRV : public IMUReport {
    float i = 0;       /**< @brief Quaternion component i */
    float j = 0;       /**< @brief Quaternion component j */
    float k = 0;       /**< @brief Quaternion component k */
    float real = 0;    /**< @brief Quaternion component real */
    float angVelX = 0; /**< @brief Angular velocity about x [rad/s] */
    float angVelY = 0; /**< @brief Angular velocity about y [rad/s] */
    float angVelZ = 0; /**< @brief Angular velocity about z [rad/s] */
};
DEPTHAI_SERIALIZE_EXT(IMUReportGyroIntegratedRV, i, j, k, real, angVelX, angVelY, angVelZ, sequence, accuracy, timestamp);

#endif

/**
 * IMU output
 *
 * Contains combined output for all possible modes. Only the enabled outputs are populated.
 */
struct IMUPacket {
    IMUReportAccelerometer acceleroMeter;
    IMUReportGyroscope gyroscope;
    IMUReportMagneticField magneticField;
    IMUReportRotationVectorWAcc rotationVector;

#if 0
    IMUReportAccelerometer rawAcceleroMeter;

    IMUReportAccelerometer linearAcceleroMeter;
    IMUReportAccelerometer gravity;

    IMUReportGyroscope rawGyroscope;
    IMUReportGyroscopeUncalibrated gyroscopeUncalibrated;

    IMUReportMagneticField rawMagneticField;
    IMUReportMagneticFieldUncalibrated magneticFieldUncalibrated;

    IMUReportRotationVector gameRotationVector;
    IMUReportRotationVectorWAcc geoMagRotationVector;

    IMUReportRotationVectorWAcc arvrStabilizedRotationVector;
    IMUReportRotationVector arvrStabilizedGameRotationVector;
    IMUReportGyroIntegratedRV gyroIntegratedRotationVector;
#endif
};

DEPTHAI_SERIALIZE_EXT(IMUPacket, acceleroMeter, gyroscope, magneticField, rotationVector);

struct RawIMUData : public RawBuffer {
    std::vector<IMUPacket> packets;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::IMUData;
    };

    DEPTHAI_SERIALIZE(RawIMUData, packets);
};

}  // namespace dai
