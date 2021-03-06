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


#ifndef _DMA_GEOSCENEMANAGER_HPP_
#define _DMA_GEOSCENEMANAGER_HPP_

#include <list>
#include <set>
#include <map>
#include <memory>

#include "glm/glm.hpp"
#include "engine/Scene.hpp"
#include "engine/geo/Poi.hpp"
#include "engine/geo/TileMap.hpp"
#include "engine/geo/PoiParams.hpp"
#include "engine/geo/LatLng.hpp"
#include "engine/geo/GeoEngineCallbacks.hpp"

namespace dma {
    namespace geo {
        class TileMap;

        /**
         * Manages a scene à la geo
         * @version 0.2.3
         */
        class GeoSceneManager {
            /* ***
             * PARAMETERS
             */

        public:

            GeoSceneManager(Scene& scene, ResourceManager& resourceManager);
            virtual ~GeoSceneManager();

            /* ***
             * PUBLIC METHODS
             * ***/

            void init();

            /**
             * unload the currently loaded scene.
             */
            void unload();

            void step();

            /**
             * Convert world coordinates to openGL coordinates.
             */
            glm::vec3 computePosition(double lat, double lon, double alt) const;

            /**
             * Adds the poi to the scene
             */
            bool addPoi(std::shared_ptr<Poi> poi);

            /**
             * remove the given Poi from the scene.
             */
            bool removePoi(const std::string& sid);

            void removeAllPois();

            bool hasPoi(const std::string& sid);

            std::shared_ptr<Poi> getPoi(const std::string& sid);

            inline Scene& getScene() {
                return mScene;
            }

            /* ***
             * SETTERS
             * ***/

            /**
             * Set the origin of the world.
             * This method should be used to prevent to have too high values for floats
             */
            void setOrigin(double lat, double lon);

            /**
             * Position the camera to the given coordinates.
             */
            void placeCamera(const LatLng& coords);
            void placeCamera(const LatLngAlt& coords);
            void placeCamera(const LatLngAlt& coords, float translationDuration, TranslationAnimation::Function translationFunction);

            void orientateCamera(std::shared_ptr<glm::mat4> rotationMatrix);

            std::shared_ptr<Poi> pick(int screenX, int screenY);

            /* ***
             * TILEMAP-PASSTHROUGHT
             */
            /**
             * Notify that a tmp png provided is available
             * @return Status::OK if tile could be loaded.
             */
            Status notifyTileAvailable(int x, int y, int z);

            void setCallbacks(GeoEngineCallbacks* callbacks);

            void setTileNamespace(const std::string& ns);

            void updateTileDiffuseMaps();

        private:
            friend class GeoEngine;
            friend class GeoEngineAsync;
            GeoSceneManager(const GeoSceneManager &) = delete;
            void operator=(const GeoSceneManager &) = delete;

            /**
             * Returns the destination point given the origin, an initial bearing and a distance
             * @param bearing in degrees
             */
            glm::vec3 destinationPoint(double bearing, double distance) const;


            /* ***
             * ATTRIBUTES
             */
            Scene& mScene;
            TileMap mTileMap;
            std::map<std::string, std::shared_ptr<Poi>> mPOIs;
            LatLng mOrigin;
            LatLngAlt mCameraCoords;
            int mLastX;
            int mLastY;
            std::shared_ptr<Poi> mSelected;
        };
    }
}

#endif // _DMA_GEOSCENEMANAGER_HPP_
