#!/usr/bin/env python

import rospy

from std_msgs.msg import Float32


rospy.init_node("gen_input")
pub = rospy.Publisher("input", Float32, queue_size=2)
msg = Float32()

period = rospy.get_param("~period", 0.8)

count = rospy.get_param("~start", 1000)

while not rospy.is_shutdown():
    count += 1
    msg.data = count
    pub.publish(msg)
    rospy.sleep(period)
