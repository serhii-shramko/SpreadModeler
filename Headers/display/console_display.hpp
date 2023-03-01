#pragma once

#include "Idisplay.hpp"

namespace sprsim {
class console_dislpay : public Idisplay {
    void showField(field &f) override;
};
} // namespace sprsim