/**
 * Copyright 2023, XGBoost Contributors
 */
#ifndef XGBOOST_DATA_BATCH_UTILS_H_
#define XGBOOST_DATA_BATCH_UTILS_H_

#include "xgboost/data.h"  // for BatchParam

namespace xgboost::data::detail {
// At least one batch parameter is initialized.
inline void CheckEmpty(BatchParam const& l, BatchParam const& r) {
  if (!l.Initialized()) {
    CHECK(r.Initialized()) << "Batch parameter is not initialized.";
  }
}

/**
 * \brief Should we regenerate the gradient index?
 *
 * \param old Parameter stored in DMatrix.
 * \param p   New parameter passed in by caller.
 */
inline bool RegenGHist(BatchParam old, BatchParam p) {
  // Parameter is renewed or caller requests a regen
  if (!p.Initialized()) {
    // Empty parameter is passed in, don't regenerate so that we can use gindex in
    // predictor, which doesn't have any training parameter.
    return false;
  }
  return p.regen || old.ParamNotEqual(p);
}

/**
 * @brief Validate the batch parameter from the caller
 */
void CheckParam(BatchParam const& init, BatchParam const& param);
}  // namespace xgboost::data::detail

namespace xgboost::cuda_impl {
// Indicator for XGBoost to not concatenate any page.
constexpr std::int64_t MatchingPageBytes() { return 0; }
// Default size of the cached page
constexpr double CachePageRatio() { return 0.125; }
// Indicator for XGBoost to not concatenate any page.
constexpr std::int64_t AutoCachePageBytes() { return -1; }
}  // namespace xgboost::cuda_impl
#endif  // XGBOOST_DATA_BATCH_UTILS_H_
