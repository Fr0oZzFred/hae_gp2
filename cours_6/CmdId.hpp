#pragma once

enum class CmdId : int {
    moveForward,
    moveBackward,
    rotateLeft,
    rotateRight,
    draw,
    Reset,
};

struct Cmd {
    CmdId id = CmdId::Reset;
    float data = 0;
};
