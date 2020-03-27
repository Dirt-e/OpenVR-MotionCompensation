#pragma once

#include <openvr_driver.h>
#include <vrmotioncompensation_types.h>
#include <openvr_math.h>
#include "../logging.h"
#include "Debugger.h"

#include <boost/timer/timer.hpp>
#include <boost/chrono/chrono.hpp>
#include <chrono\system_clocks.hpp>

// driver namespace
namespace vrmotioncompensation
{
	namespace driver
	{
		// forward declarations
		class ServerDriver;
		class DeviceManipulationHandle;


		class MotionCompensationManager
		{
		public:
			MotionCompensationManager(ServerDriver* parent) : m_parent(parent)
			{
			}
			
			void WriteDebugData();

			void setMotionCompensationMode(MotionCompensationMode Mode);

			void setLPFBeta(double NewBeta)
			{
				LPF_Beta = NewBeta;
			}

			double getLPFBeta()
			{
				return LPF_Beta;
			}

			bool _isMotionCompensationZeroPoseValid();
			
			void _setMotionCompensationZeroPose(const vr::DriverPose_t& pose);
			
			void _updateMotionCompensationRefPose(const vr::DriverPose_t& pose);
			
			bool _applyMotionCompensation(vr::DriverPose_t& pose, DeviceManipulationHandle* deviceInfo);

			void runFrame();

			vr::HmdVector3d_t LPF(const double RawData[3], vr::HmdVector3d_t SmoothData);

			vr::HmdVector3d_t LPF(vr::HmdVector3d_t RawData, vr::HmdVector3d_t SmoothData);

			vr::HmdQuaternion_t lowPassFilterQuaternion(vr::HmdQuaternion_t RawData, vr::HmdQuaternion_t SmoothData);			

			vr::HmdQuaternion_t Slerp(vr::HmdQuaternion_t q1, vr::HmdQuaternion_t q2, double lambda);

			vr::HmdVector3d_t ToEulerAngles(vr::HmdQuaternion_t q);

			const double AngleDifference(double angle1, double angle2);

		private:
			ServerDriver* m_parent;

			Debugger DebugLogger;

			double LPF_Beta = 0.2;

			bool _motionCompensationEnabled = false;
			MotionCompensationMode _motionCompensationMode = MotionCompensationMode::Disabled;			
			
			// Zero position
			vr::HmdVector3d_t _motionCompensationZeroPos;
			vr::HmdQuaternion_t _motionCompensationZeroRot;
			bool _motionCompensationZeroPoseValid = false;
			
			// Reference position
			vr::HmdVector3d_t _motionCompensationRefPos;
			vr::HmdVector3d_t _Filter_vecPosition_1;
			vr::HmdVector3d_t _Filter_vecPosition_2;
			vr::HmdVector3d_t _Filter_vecPosition_3;

			vr::HmdVector3d_t _motionCompensationRefPosVel;
			vr::HmdVector3d_t _motionCompensationRefPosAcc;

			vr::HmdQuaternion_t _motionCompensationRefRot;
			vr::HmdQuaternion_t _motionCompensationRefRotInv;
			vr::HmdQuaternion_t _Filter_rotPosition_1;
			vr::HmdQuaternion_t _Filter_rotPosition_2;
			vr::HmdQuaternion_t _Filter_rotPosition_3;

			vr::HmdVector3d_t _motionCompensationRefRotVel;
			vr::HmdVector3d_t _motionCompensationRefRotAcc;

			bool _motionCompensationRefPoseValid = false;
		};
	}
}