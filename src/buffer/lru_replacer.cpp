//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.cpp
//
// Identification: src/buffer/lru_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_replacer.h"

namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) {
  this->max_num_pages_ = num_pages;
  this->victim_page_ = nullptr;
}

LRUReplacer::~LRUReplacer() = default;

bool LRUReplacer::Victim(frame_id_t *frame_id) {
  if(Size() == 0) {
    return false;
  }
  frame_id = &pages_queue_.front();
  victim_page_ = frame_id;
  // pop it
  pages_queue_.pop_front();
  return true; }

void LRUReplacer::Pin(frame_id_t frame_id) {
  // check if frame_id is in the pool
  auto it = std::find(pages_queue_.begin(), pages_queue_.end(), frame_id);
  if (it != pages_queue_.end()){
    // frame is found
    // set pin count to 1 I think
    pin_counts_[frame_id] = 1;
  }
}

void LRUReplacer::Unpin(frame_id_t frame_id) {
  if (pages_queue_.size() == max_num_pages_){
    // maximum capacity reached

  } else{
    // check if frame_id exists
    auto it  = std::find(pages_queue_.begin(), pages_queue_.end(), frame_id);
    if (it == pages_queue_.end()){
      // element does not exist
      // push it back
      pages_queue_.push_back(frame_id);
    } else{
      // element exists
      pages_queue_.remove(frame_id);
      // push it back
      pages_queue_.push_back(frame_id);
    }

  }
}

size_t LRUReplacer::Size() { return pages_queue_.size(); }

}  // namespace bustub
