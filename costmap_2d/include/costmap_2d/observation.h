/*
 * Copyright (c) 2008, 2013, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Conor McGann
 */

#ifndef COSTMAP_2D_OBSERVATION_H_
#define COSTMAP_2D_OBSERVATION_H_

#include <geometry_msgs/Point.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

namespace costmap_2d
{

/**
 * @brief Stores an observation in terms of a point cloud and the origin of the source
 * @note Tried to make members and constructor arguments const but the compiler would not accept the default
 * assignment operator for vector insertion!
 */
class Observation
{
public:
  /**
   * @brief  Creates an empty observation
   */
  Observation() :
    cloud_(new pcl::PointCloud<pcl::PointXYZ>()), max_obstacle_range_(0.0), max_raytrace_range_(0.0), min_raytrace_range_(0.0),
    orientation_in_global_frame_(0.0), fov_(0.0)
  {
  }

  virtual ~Observation()
  {
    delete cloud_;
  }

  /**
   * @brief  Creates an observation from an origin point and a point cloud.
   * This constructor is deprecated, use the constructor with min and max raytrace range now.
   * @param origin The origin point of the observation
   * @param cloud The point cloud of the observation
   * @param max_obstacle_range The range out to which an observation should be able to insert obstacles
   * @param max_raytrace_range The range out to which an observation should be able to clear via raytracing
   */
  ROS_DEPRECATED
  Observation(geometry_msgs::Point& origin, pcl::PointCloud<pcl::PointXYZ> cloud,
              double max_obstacle_range, double max_raytrace_range) :
      origin_(origin), cloud_(new pcl::PointCloud<pcl::PointXYZ>(cloud)), min_obstacle_range_(0.0),
      max_obstacle_range_(max_obstacle_range), min_raytrace_range_(0.0), max_raytrace_range_(max_raytrace_range)
  {
  }

  /**
   * @brief  Creates an observation from an origin point and a point cloud
   * @param origin The origin point of the observation
   * @param cloud The point cloud of the observation
   * @param min_obstacle_range The range from which an observation should be able to insert obstacles
   * @param max_obstacle_range The range out to which an observation should be able to insert obstacles
   * @param min_raytrace_range The range from which an observation should be able to clear via raytracing
   * @param max_raytrace_range The range out to which an observation should be able to clear via raytracing
   * @param orientation_in_global_frame : Sensor orientation in global frame (to be able to compute theoretical
   * FOV of this sensor).
   */
  Observation(geometry_msgs::Point& origin, pcl::PointCloud<pcl::PointXYZ> cloud,
              double min_obstacle_range, double max_obstacle_range, double min_raytrace_range,
              double max_raytrace_range, double orientation_in_global_frame, double fov) :
          origin_(origin), cloud_(new pcl::PointCloud<pcl::PointXYZ>(cloud)),min_obstacle_range_(min_obstacle_range),
          max_obstacle_range_(max_obstacle_range), min_raytrace_range_(min_raytrace_range),
          max_raytrace_range_(max_raytrace_range), orientation_in_global_frame_(orientation_in_global_frame), fov_(fov)
  {
  }

  /**
   * @brief  Copy constructor
   * @param obs The observation to copy
   */
  Observation(const Observation& obs) :
      origin_(obs.origin_), cloud_(new pcl::PointCloud<pcl::PointXYZ>(*(obs.cloud_))),
      min_obstacle_range_(obs.min_obstacle_range_), max_obstacle_range_(obs.max_obstacle_range_),
      min_raytrace_range_(obs.min_raytrace_range_), max_raytrace_range_(obs.max_raytrace_range_),
      orientation_in_global_frame_(obs.orientation_in_global_frame_), fov_(obs.fov_)
  {
  }

  /**
   * @brief  Creates an observation from a point cloud
   * @param cloud The point cloud of the observation
   * @param max_obstacle_range The range out to which an observation should be able to insert obstacles
   */
  Observation(pcl::PointCloud<pcl::PointXYZ> cloud, double max_obstacle_range) :
      cloud_(new pcl::PointCloud<pcl::PointXYZ>(cloud)), min_obstacle_range_(0.0),
      max_obstacle_range_(max_obstacle_range), min_raytrace_range_(0.0), max_raytrace_range_(0.0),
      orientation_in_global_frame_(0.0), fov_(0.0)
  {
  }

  geometry_msgs::Point origin_;
  pcl::PointCloud<pcl::PointXYZ>* cloud_;
  double min_obstacle_range_, max_obstacle_range_, min_raytrace_range_, max_raytrace_range_, orientation_in_global_frame_;
  double fov_;
};

}  // namespace costmap_2d
#endif  // COSTMAP_2D_OBSERVATION_H_
