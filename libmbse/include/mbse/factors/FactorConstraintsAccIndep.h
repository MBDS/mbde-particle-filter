/*+-------------------------------------------------------------------------+
  |            Multi Body State Estimation (mbse) C++ library               |
  |                                                                         |
  | Copyright (C) 2014-2020 University of Almeria                           |
  | Copyright (C) 2020 University of Salento                                |
  | See README for list of authors and papers                               |
  | Distributed under 3-clause BSD license                                  |
  |  See: <https://opensource.org/licenses/BSD-3-Clause>                    |
  +-------------------------------------------------------------------------+ */

#pragma once

#include <mbse/factors/factor-common.h>
#include <gtsam/nonlinear/NonlinearFactor.h>
#include <mbse/CAssembledRigidModel.h>

namespace mbse
{
/** Factor for acceleration constraints in independent coordinates.
 * Here the constraints equation \dot{\PHI}_{\q}(\q_t)\dq_t + \Phiq(\q_t)\ddq_t is implemented; for fixed
 * constraints Phi_t(q)=0.
 */
class FactorConstraintsAccIndep
	: public gtsam::NoiseModelFactor4<
		  state_t /*Q*/, state_t /*dotQ*/,state_t /*ddotQ*/, state_t /*ddotZ*/>
{
   private:
	using This = FactorConstraintsAccIndep;
	using Base = gtsam::NoiseModelFactor4<
		state_t /*Q*/, state_t /*dotQ*/,state_t /*ddotQ*/, state_t /*ddotZ*/>;

	// Class parameters (pointer to type "CConstraintBase")
	CAssembledRigidModel::Ptr arm_;
	std::vector<size_t> indCoordsIndices_;
	gtsam::Matrix matrix_Iidx_;

   public:
	// shorthand for a smart pointer to a factor
	using shared_ptr = boost::shared_ptr<This>;

	/** default constructor - only use for serialization */
	FactorConstraintsAccIndep() = default;

	/** Construcotr */
	FactorConstraintsAccIndep(
		const CAssembledRigidModel::Ptr& arm,
		const std::vector<size_t>& indCoordsIndices,
		const gtsam::SharedNoiseModel& noiseModel, gtsam::Key key_q_k,
		gtsam::Key key_dotq_k, gtsam::Key key_ddotq_k,gtsam::Key key_ddotz_k);

	virtual ~FactorConstraintsAccIndep() override;

	// @return a deep copy of this factor
	virtual gtsam::NonlinearFactor::shared_ptr clone() const override;
	/** implement functions needed for Testable */
	/** print */
	virtual void print(
		const std::string& s, const gtsam::KeyFormatter& keyFormatter =
								  gtsam::DefaultKeyFormatter) const override;

	/** equals */
	virtual bool equals(
		const gtsam::NonlinearFactor& expected,
		double tol = 1e-9) const override;

	/** implement functions needed to derive from Factor */
	/** vector of errors */
	gtsam::Vector evaluateError(
		const state_t& q_k, const state_t& dotq_k, const state_t& ddotq_k, const state_t& ddotz_k,
		boost::optional<gtsam::Matrix&> de_dq = boost::none,
		boost::optional<gtsam::Matrix&> de_dqp = boost::none,
		boost::optional<gtsam::Matrix&> de_dqpp = boost::none,
		boost::optional<gtsam::Matrix&> de_dzpp = boost::none) const override;

	/** numberof variable attached to this factor */
	std::size_t size() const { return 4; }

   private:
	/** Serialization function */
	friend class boost::serialization::access;
	template <class ARCHIVE>
	void serialize(ARCHIVE& ar, const unsigned int /*version*/)
	{
		ar& boost::serialization::make_nvp(
			"FactorConstraintsAccIndep",
			boost::serialization::base_object<Base>(*this));
	}
};

}  // namespace mbse
