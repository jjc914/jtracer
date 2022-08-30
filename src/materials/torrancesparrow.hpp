#ifndef torrancesparrow_hpp
#define torrancesparrow_hpp

#include "brdf.hpp"
#include "microfacets/microfacetdistribution.hpp"
#include "math/math.hpp"

using namespace math;

namespace materials {

    class torrancesparrow : public brdf { //TODO: Oren-Nayar microfacet reflection
    public:
        // microfacet(const color albedo, const double alphaX, const double alphaY, const color emissionColor = color(0.0, 0.0, 0.0), const double emissionPower = 0.0);
        torrancesparrow(const color albedo, microfacetdistribution* distribution, const color emissionColor = color(0.0, 0.0, 0.0), const double emissionPower = 0.0);
        
        color evaluate(const vec3<double> wo, const vec3<double> wi) const;
        // void test();
    private:
        microfacetdistribution* distribution;
        // constexpr static double ONE_SIXTH = 1.0 / 6.0;

        // double alphaX, alphaY;
        // double invAlphaXSqr, invAlphaYSqr, invDenomConst;

        // double pdf(const double beta, const double phi) const;
        // // https://www.desmos.com/calculator/ssmliq9dg5
        // double maxProbPhi(const double phi) const;
        // // https://www.desmos.com/calculator/wbnosakwqd
        // double maxProbBeta(const double beta) const;
        // double randomSampleBeta(const double phi) const;
        // double randomSamplePhi(const double beta) const;
    };
}

#endif
