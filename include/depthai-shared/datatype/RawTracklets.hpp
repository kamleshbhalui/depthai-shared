#pragma once

#include <iostream>

#include "RawBuffer.hpp"
#include "depthai-shared/common/Point3f.hpp"
#include "depthai-shared/common/Rect.hpp"
#include "depthai-shared/datatype/RawImgDetections.hpp"

namespace dai {

/**
 * Tracklet structure
 *
 * Contains tracklets from object tracker output.
 */
struct Tracklet {
    enum class TrackingStatus : std::int32_t {
        NEW,     /**< The object is newly added. */
        TRACKED, /**< The object is being tracked. */
        LOST /**< The object gets lost now. The object can be tracked again automatically(long term tracking) or by specifying detected object manually(short
                term and zero term tracking). */
    };
    Rect roi;
    std::int32_t id;
    std::int32_t label;
    TrackingStatus status;

    ImgDetection srcImgDetection;
    Point3f spatialCoordinates;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Tracklet, roi, id, label, status, srcImgDetection, spatialCoordinates);
};

inline std::ostream& operator<<(std::ostream& out, Tracklet::TrackingStatus& status) {
    switch(status) {
        case Tracklet::TrackingStatus::NEW:
            out << "NEW";
            break;
        case Tracklet::TrackingStatus::TRACKED:
            out << "TRACKED";
            break;
        case Tracklet::TrackingStatus::LOST:
            out << "LOST";
            break;
    }
    return out;
}

struct RawTracklets : public RawBuffer {
    std::vector<Tracklet> tracklets;

    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) override {
        nlohmann::json j = *this;
        metadata = nlohmann::json::to_msgpack(j);
        datatype = DatatypeEnum::Tracklets;
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RawTracklets, tracklets);
};

}  // namespace dai
