#pragma once

#include <smacc2/smacc.hpp>
#include <sensor_msgs/msg/joy.hpp>

namespace sm_sample
{

// イベント定義
struct EvControllerConnected   : sc::event<EvControllerConnected> {};
struct EvControllerDisconnected: sc::event<EvControllerDisconnected> {};

class CpJoyMonitor : public smacc2::ISmaccComponent
{
public:
  void onInitialize() override
  {
    auto node = getNode();
    last_msg_time_ = node->now();
    controller_connected_ = false;

    sub_ = node->create_subscription<sensor_msgs::msg::Joy>(
      "joy", 10,
      [this](const sensor_msgs::msg::Joy::SharedPtr)
      {
        auto now = this->getNode()->now();
        last_msg_time_ = now;

        if (!controller_connected_)
        {
          controller_connected_ = true;
          RCLCPP_INFO(getNode()->get_logger(), "Joy connected");
          this->getStateMachine()->postEvent<EvControllerConnected>();
        }
      });

    // タイマーで一定周期チェック
    timer_ = node->create_wall_timer(
      std::chrono::milliseconds(200),
      [this]()
      {
        auto now = this->getNode()->now();
        if (controller_connected_ &&
            (now - last_msg_time_).seconds() > timeout_sec_)
        {
          controller_connected_ = false;
          RCLCPP_WARN(getNode()->get_logger(), "Joy disconnected (timeout)");
          this->getStateMachine()->postEvent<EvControllerDisconnected>();
        }
      });
  }

private:
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Time last_msg_time_;
  bool controller_connected_{false};
  double timeout_sec_{1.0};  // 1秒以上来なかったら切断と見なす
};

} // namespace sm_sample
