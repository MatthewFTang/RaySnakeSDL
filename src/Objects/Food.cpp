//
// Created by Matt on 3/07/2024.
//

#include "Food.h"

void Food::Update() {
    if (m_frame_count_ == GetAnimationSpeed()) {
        int frame = GetCurrentFrame();
        frame++;
        if (frame == GetNumFrames()) frame = 0;
        SetCurrentFrame(frame);
        m_frame_count_ = 0;
    }
    m_frame_count_++;
}
