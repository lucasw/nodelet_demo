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

#include <cv_bridge/cv_bridge.h>
#include <nodelet_demo/nodelet_demo.h>
#include <nodelet_demo/utility.h>


namespace nodelet_demo
{

NodeletDemo::NodeletDemo() :
  spinner_(4)
{
}

NodeletDemo::~NodeletDemo()
{
}

#if 0
void NodeletDemo::drCallback(
    nodelet_demo::DemoConfig& config,
    uint32_t level)
{
  config_ = config;
}
#endif

void NodeletDemo::callback(const std_msgs::Float32ConstPtr& msg)
{
  ROS_INFO_STREAM("start | msg " << msg->data << ", cpu id " << get_cpu_id());
  // TODO(lucasw) cpu id can change after either of these waiting methods?
  if (!busy_wait_)
  {
    ROS_WARN_STREAM_ONCE("not using busy wait, ros sleeping");
    ros::Duration(callback_delay_).sleep();
  }
  else
  {
    ROS_WARN_STREAM_ONCE("using busy wait");
    ros::Time t0 = ros::Time::now();
    while ((ros::Time::now() - t0).toSec() < callback_delay_)
    {
    }
  }

  pub_.publish(msg);
  ROS_INFO_STREAM("done  | msg " << msg->data << ", cpu id " << get_cpu_id());
}

#if 0
void NodeletDemo::update(const ros::TimerEvent& e)
{
}
#endif

void NodeletDemo::onInit()
{
  bool mt_callback = false;
  getPrivateNodeHandle().getParam("mt_callback", mt_callback);
  // auto getNH = &nodelet_demo::NodeletDemo::getPrivateNodeHandle;
  ros::NodeHandle nh;
  ros::NodeHandle pnh;
  if (mt_callback)
  {
    ROS_INFO_STREAM("using multi-threaded node handles");
    nh = getMTNodeHandle();
    pnh = getMTPrivateNodeHandle();
  }
  else
  {
    ROS_INFO_STREAM("using single-threaded node handles");
    nh = getNodeHandle();
    pnh = getPrivateNodeHandle();
  }

  // This results in error:
  // Attempt to spin a callback queue from two spinners, one of them being single-threaded.
  // spinner_.start();

  int output_queue_size = 10;
  pnh.getParam("output_queue_size", output_queue_size);
  pub_ = nh.advertise<std_msgs::Float32>("output", output_queue_size);

  pnh.getParam("callback_delay", callback_delay_);
#if 0
  server_.reset(new ReconfigureServer(dr_mutex_, pnh));
  dynamic_reconfigure::Server<nodelet_demo::DelayConfig>::CallbackType cbt =
      boost::bind(&NodeletDemo::callback, this, boost::placeholders::_1, boost::placeholders::_2);
  server_->setCallback(cbt);
#endif

  pnh.getParam("busy_wait", busy_wait_);

  int input_queue_size = 10;
  pnh.getParam("input_queue_size", input_queue_size);

  // TODO(lucasw) setup sub2 like this also?
  ros::SubscribeOptions so1;
  so1.init<std_msgs::Float32>(
      "input1",
      input_queue_size,
      boost::bind(&NodeletDemo::callback, this, boost::placeholders::_1));

  so1.allow_concurrent_callbacks = true;

  sub1_ = nh.subscribe(so1);
#if 0
  sub2_ = nh.subscribe("input2", input_queue_size,
      &NodeletDemo::callback, this);
#endif

#if 0
  // this crashes the manager
  if (mt_callback)
  {
    sub2_ = nh.subscribe("input1", input_queue_size,
        &NodeletDemo::callback, this);
  }
#endif

  // timer_ = pnh.createTimer(ros::Duration(1.0),
  //     &NodeletDemo::update, this);
}

};  // namespace nodelet_demo

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(nodelet_demo::NodeletDemo, nodelet::Nodelet)

#include <nodelet_topic_tools/nodelet_demux.h>
typedef nodelet::NodeletDEMUX<std_msgs::Float32> Float32NodeletDemux;
PLUGINLIB_EXPORT_CLASS(Float32NodeletDemux, nodelet::Nodelet);
