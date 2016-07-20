/*
 ofxKinectFeatures
 Copyright © 2014 Music Technology Group - Universitat Pompeu Fabra / Escola Superior de Música de Catalunya
 
 This file is part of ofxKinectFeatures, created and maintained by Álvaro Sarasúa <http://www.alvarosarasua.com>
 
 ofxKinectFeatures is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License (LGPL v3) as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 
 ofxKinectFeatures is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License (LGPL v3).
 
 You should have received a copy of the GNU Lesser General Public License long within the ofxKinectFeatures SW package.  If not, see <http://www.gnu.org/licenses/>.
 
 If you are willing to get a (non FOSS) commercial license, please contact us at mtg@upf.edu
 */

#ifndef mode_joint_h
#define mode_joint_h

#include "mode_descriptor.h"
#include <iostream>

namespace MoDe {

	enum
	{
		FEAT_POSITION,
		FEAT_POSITION_FILTERED,
		FEAT_VELOCITY,
		FEAT_ACCELERATION,
		FEAT_ACCELERATION_TRAJECTORY,
		FEAT_RELATIVEPOSTOTORSO,
		FEAT_QOM,
		FEAT_CI
	};

    class MoDeJoint{
    public:
        MoDeJoint() : position(0), positionFiltered(0), velocity(0), acceleration(0), accelerationTrajectory(0), relativePositionToTorso(0) {};
        MoDeJoint(int elementId, int depth) : position(depth), positionFiltered(depth), velocity(depth), acceleration(depth), accelerationTrajectory(depth), relativePositionToTorso(depth){
            elementId_ = elementId;
            historyDepth_ = depth;
        }
        
        unsigned int getElementId(){
            return elementId_;
        }
        
        void setElementId(int newId){
            elementId_ = newId;
        }

		MoDeDescriptor<MoDePoint> getDescriptor(unsigned int descriptorId) const {
			switch (descriptorId)
			{
			case FEAT_POSITION:
				return position;
			case FEAT_POSITION_FILTERED:
				return positionFiltered;
			case FEAT_VELOCITY:
				return velocity;
			case FEAT_ACCELERATION:
				return acceleration;
			case FEAT_RELATIVEPOSTOTORSO:
				return relativePositionToTorso;
			default:
				throw runtime_error("Descriptor ID doesn't match any existing 3D descriptor");
			}
		}
		MoDeDescriptor<float> getUniDescriptor(int descriptorId) const {
			switch (descriptorId)
			{
			case FEAT_ACCELERATION_TRAJECTORY:
				return accelerationTrajectory;
			default:
				throw runtime_error("Descriptor ID doesn't match any existing 1D descriptor");
			}
		}

		void addValue(unsigned int descriptorId, MoDePoint value) {
			switch (descriptorId)
			{
			case FEAT_POSITION:
				position.push(value);
			case FEAT_POSITION_FILTERED:
				positionFiltered.push(value);
			case FEAT_VELOCITY:
				velocity.push(value);
			case FEAT_ACCELERATION:
				acceleration.push(value);
			case FEAT_RELATIVEPOSTOTORSO:
				relativePositionToTorso.push(value);
			default:
				throw runtime_error("Descriptor ID doesn't match any existing 3D descriptor");
			}
		}

		void addValue(unsigned int descriptorId, float value) {
			switch (descriptorId)
			{
			case FEAT_ACCELERATION_TRAJECTORY:
				accelerationTrajectory.push(value);
			default:
				throw runtime_error("Descriptor ID doesn't match any existing 1D descriptor");
			}
		}
       
	private:
        MoDeDescriptor<MoDePoint> position;
        MoDeDescriptor<MoDePoint> positionFiltered;
        MoDeDescriptor<MoDePoint> velocity;
        MoDeDescriptor<MoDePoint> acceleration;    
        MoDeDescriptor<float> accelerationTrajectory;
        MoDeDescriptor<MoDePoint> relativePositionToTorso;

        int historyDepth_;
        int elementId_;    
    };
}

#endif
