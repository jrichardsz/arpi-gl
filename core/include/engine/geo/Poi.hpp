/*
 * Copyright (C) 2015  eBusiness Information
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _DMA_POI_HPP_
#define _DMA_POI_HPP_

#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <utils/Color.hpp>
#include <rendering/Selectable.hpp>
#include <glm/gtc/type_ptr.hpp>     // make_mat4
#include "engine/Entity.hpp"
#include "animation/RotationAnimation.hpp"
#include "LatLngAlt.hpp"

namespace dma {
    namespace geo {
        class GeoSceneManager;

        /**
         * Poi variation of an Entity. A poi, or Point of Interest, represents
         * a precise point located in space.
         * It is described by a shape, a material, and its position.
         *
         * @version 0.2.3
         */
        class Poi : public Entity, public Selectable {

        public:
            Poi(const std::string& sid, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
            Poi(const Poi &) = delete;
            void operator=(const Poi &) = delete;
            virtual ~Poi();


            /* ***
             * GETTERS
             */

            /** /!\ CAN BE EMPTY */
            inline const std::string& getSid() const { return mSID; }

            /**
             * @param double*
             *              will be filled with { lat, lon, alt }.
             */
            void getPosition(double*);


            /**
             * Returns the latitude of the poi
             */
            inline double getLat() const { return mLat; }

            /**
             * Returns the longitude of the poi
             */
            inline double getLng() const { return mLon; }


            /**
             * Returns the longitude of the poi
             */
            inline double getAlt() const { return mAlt; }

            /* ***
             * SETTERS
             */
            /**
             * Set the position for this poi.
             * @param double -
             *              latitude of this entity.
             * @param double -
             *              longitude of this entity.
             * @param double -
             *              altitude of this entity.
             */
            void setPosition(double lat, double lon, double alt = 0.0);

            /**
             * Set the poi position.
             * @param double pos[3]
             *              the position of the POI. Must be of length 3.
             */
            inline void setPosition(double pos[3]) {
                setPosition(pos[0], pos[1], pos[2]);
            }

            void setColor(const Color& color);

            /**
             * Set the POI orientation.
             *
             * @param const float*
             *            the orientation matrix.
             */
            inline void setOrientation(const float orientationMat[16]) {
                const glm::mat4& rotationMatrix = glm::make_mat4(orientationMat);
                Entity::setOrientation(rotationMatrix);
            }

            void animate();
            void deanimate();

            inline std::shared_ptr<Material> getMaterial() {
                return mRenderingComponent->getRenderingPackages()[0]->getMaterial();
            }

            inline std::shared_ptr<Mesh> getMesh() {
                return mRenderingComponent->getMesh();
            }

            inline bool isDirty() const {
                return mDirty;
            }

            inline void setDirty(bool dirty) {
                mDirty = dirty;
            }

            virtual bool intersects(const glm::vec3 &ray, const glm::vec3& origin);


            /**
             * Updates POI poisition & animation, against the provided GeoSceneMagager
             */
            //void update(const GeoSceneManager& sceneManager);

            /* ***
             * ATTRIBUTES
             */

        protected:
            const std::string mSID;
            double mLat;
            double mLon;
            double mAlt;
            bool mDirty;
            TranslationAnimation* mCurrentTranslationAnimation;
            RotationAnimation* mCurrentRotationAnimation;
        };
    }
}

#endif //_DMA_POI_HPP_
