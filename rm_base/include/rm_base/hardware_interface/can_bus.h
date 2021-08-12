/*******************************************************************************
 * BSD 3-Clause License
 *
 * Copyright (c) 2021, Qiayuan Liao
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************/
 
//
// Created by qiayuan on 12/28/20.
//

#ifndef RM_BASE_INCLUDE_RM_BASE_CAN_BUS_H_
#define RM_BASE_INCLUDE_RM_BASE_CAN_BUS_H_

#include "rm_base/hardware_interface/socketcan.h"
#include "rm_base/hardware_interface/types.h"

#include <chrono>
#include <mutex>
#include <thread>

namespace rm_base {
struct CanFrameStamp {
  can_frame frame;
  ros::Time stamp;
};

class CanBus {
 public:
  CanBus(const std::string &bus_name, CanDataPtr data_prt);
  void read(ros::Time time);
  void write();
 private:
  void frameCallback(const can_frame &frame);

  can::SocketCAN socket_can_;
  CanDataPtr data_prt_;
  std::string bus_name_;
  std::vector<CanFrameStamp> read_buffer_;

  can_frame rm_frame0_{};  // for id 0x201~0x204
  can_frame rm_frame1_{};  // for id 0x205~0x208

  mutable std::mutex mutex_;
};

}

#endif  //RM_BASE_INCLUDE_RM_BASE_CAN_BUS_H_
