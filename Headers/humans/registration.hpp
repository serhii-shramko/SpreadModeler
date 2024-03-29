#pragma once

namespace sprsim {
struct registration {
  unsigned long work_id;
  unsigned long home_id;
  unsigned long hospital_id;

  registration() : work_id(0), home_id(0), hospital_id(0) {}

  registration(unsigned long in_work_id, unsigned long in_home_id,
               unsigned long in_hospital_id)
      : work_id(in_work_id), home_id(in_home_id), hospital_id(in_hospital_id) {}
};
} // namespace sprsim