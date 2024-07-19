//
// Created by Matt on 3/07/2024.
//

#pragma once
#include "GameObject.h"

class Food : public GameObject {
 public:
  using GameObject::GameObject;;

  std::string GetGameObjectType() override { return "Food"; }
  void Update() override;

 private:
  int m_frame_count_ = 0;
};
