/*
 * Copyright (c) 2017 Lucas Walter
 * June 2017
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
 */

#ifndef NODELET_DEMO_NODELET_DEMO_H
#define NODELET_DEMO_NODELET_DEMO_H

#include <dynamic_reconfigure/server.h>
// #include <nodelet_demo/DelayConfig.h>
#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <std_msgs/Float32.h>

namespace nodelet_demo
{

class NodeletDemo : public nodelet::Nodelet
{
  ros::Publisher pub_;
  ros::Subscriber sub1_;
  ros::Subscriber sub2_;

  ros::AsyncSpinner spinner_;
  #if 0
  nodelet_demo::DelayConfig config_;
  typedef dynamic_reconfigure::Server<nodelet_demo::DelayConfig> ReconfigureServer;
  boost::shared_ptr< ReconfigureServer > server_;
  void callback(nodelet_demo::DelayConfig& config,
      uint32_t level);
  boost::recursive_mutex dr_mutex_;
  #endif

  float callback_delay_;
  void callback(const std_msgs::Float32ConstPtr& msg);
  // ros::Timer timer_;
  // void update(const ros::TimerEvent& e);

public:
  virtual void onInit();
  NodeletDemo();
  ~NodeletDemo();
};

}  // namespace nodelet_demo

#endif  // NODELET_DEMO_NODELET_DEMO_H
