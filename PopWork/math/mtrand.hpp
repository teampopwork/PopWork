#ifndef __MTRAND_HPP__
#define __MTRAND_HPP__
#ifdef _WIN32
#pragma once
#endif

#include <string>
#include <random>
#include <sstream>
#include <limits>
#include <atomic>

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

namespace PopWork
{

#define MTRAND_N 624

class MTRand
{
  public:
	explicit MTRand(unsigned long seed = 4357UL)
		: engine(seed), dist_int(0, std::numeric_limits<unsigned long>::max()), dist_real(0.0f, 1.0f)
	{
	}

	explicit MTRand(const std::string &serialData)
	{
		std::seed_seq seq(serialData.begin(), serialData.end());
		engine.seed(seq);
	}

	void SRand(unsigned long seed)
	{
		engine.seed(seed == 0 ? 4357UL : seed);
	}

	void SRand(const std::string &serialData)
	{
		std::seed_seq seq(serialData.begin(), serialData.end());
		engine.seed(seq);
	}

	unsigned long Next()
	{
		return NextNoAssert();
	}

	unsigned long NextNoAssert()
	{
		return dist_int(engine);
	}

	unsigned long NextNoAssert(unsigned long range)
	{
		return NextNoAssert() % range;
	}

	unsigned long Next(unsigned long range)
	{
		return NextNoAssert(range);
	}

	float NextNoAssert(float range)
	{
		return dist_real(engine) * range;
	}

	float Next(float range)
	{
		return NextNoAssert(range);
	}

	std::string Serialize() const
	{
		std::ostringstream ss;
		ss << engine;
		return ss.str();
	}

	void Deserialize(const std::string &state)
	{
		std::istringstream ss(state);
		ss >> engine;
	}

	static void SetRandAllowed(bool allowed)
	{
		if (allowed)
		{
			if (gRandAllowed > 0)
				--gRandAllowed;
		}
		else
		{
			++gRandAllowed;
		}
	}

  private:
	std::mt19937 engine;
	std::uniform_int_distribution<unsigned long> dist_int;
	std::uniform_real_distribution<float> dist_real;

	static inline std::atomic<int> gRandAllowed{0};
};

struct MTAutoDisallowRand
{
	MTAutoDisallowRand()
	{
		MTRand::SetRandAllowed(false);
	}
	~MTAutoDisallowRand()
	{
		MTRand::SetRandAllowed(true);
	}
};

} // namespace PopWork

#endif
