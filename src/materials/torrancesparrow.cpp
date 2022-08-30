#include <iostream>

#include "torrancesparrow.hpp"

namespace materials {

    // microfacet::microfacet(const color albedo, const double alphaX, const double alphaY, const color emissionColor, const double emissionPower) : brdf(albedo, emissionColor, emissionPower), alphaX(alphaX), alphaY(alphaY) {
    //     invAlphaXSqr = 1 / (alphaX * alphaX);
    //     invAlphaYSqr = 1 / (alphaY * alphaY);
    //     invDenomConst = 1 / (M_PI * alphaX * alphaY);
    // }
    torrancesparrow::torrancesparrow(const color albedo, microfacetdistribution* distribution, const color emissionColor, const double emissionPower) : brdf(albedo, emissionColor, emissionPower), distribution(distribution) {
    }

    color torrancesparrow::evaluate(const vec3<double> wo, const vec3<double> wi) const {
        double cosThetaO = std::abs(cosZenith(wo));
        double cosThetaI = std::abs(cosZenith(wi));

        vec3<double> wh = (wo + wi).normalize();
        if (cosThetaI < std::numeric_limits<double>::epsilon() || 
            cosThetaO < std::numeric_limits<double>::epsilon()) return color(0.0, 0.0, 0.0);
        if (wh.getX() < std::numeric_limits<double>::epsilon() &&
            wh.getY() < std::numeric_limits<double>::epsilon() &&
            wh.getZ() < std::numeric_limits<double>::epsilon()) return color(0.0, 0.0, 0.0);

        return getAlbedo() * distribution->d(wh) * distribution->g(wo, wi) / (4.0 * cosThetaI * cosThetaO);
    }

    // vec3<double> beckspizz::sampleBounceDirection(vec3<double> inDirection, vec3<double> normal) const {
    //     normal.normalize();
    //     inDirection.normalize();
    //     // find rotation matrix (mat) to transform normal into vec3(0.0, 1.0, 0.0)
    //     mat3x3<double> R = mat3x3<double>::align(normal, vec3<double>(0.0, 1.0, 0.0));

    //     // transform inDirection by mat
    //     vec3<double> I = R * inDirection;

    //     // get azimuth and elevation of inDirection
    //     double E = std::atan(I.getY() / std::sqrt(I.getZ() * I.getZ() + I.getX() * I.getX()));
    //     double A = std::atan(-I.getZ() / I.getX()); // this does not tecnically produce the correct answer, but thanks to trig it works!
    //     // std::cout << "elevation: " << rad2deg(E) << ", azimuth: " << rad2deg(A) << std::endl;

    //     // get random angles using azimuth and elevation
    //     double dE = randomSampleBeta(A);
    //     double dA = randomSamplePhi(M_PI_2 - E);

    //     vec3<double> O = vec3<double>::reflect(inDirection, normal);
    //     O = mat3x3<double>::rotate(O, vec3<double>(0.0, 1.0, 0.0), dA);
    //     O = mat3x3<double>::rotate(O, vec3<double>::cross(inDirection, normal).normalize(), dE);
    //     // mat3x3<double> rot = mat3x3<double>(std::cos(dA), -std::sin(dA), 0,
    //     //                                     std::sin(dA),  std::cos(dA), 0,
    //     //                                     0,             0,            1) *
    //     //                      mat3x3<double>(std::cos(dE),  0,            std::sin(dE),
    //     //                                     0,             1,            0,
    //     //                                     -std::sin(dE), 0,            std::cos(dE));
    //     // double asdf = 0.0;
    //     // mat3x3<double> rot = mat3x3<double>(std::cos(asdf), -std::sin(asdf), 0,
    //     //                                     std::sin(asdf),  std::cos(asdf), 0,
    //     //                                     0,               0,              1);
    //     // mat3x3<double> rot = mat3x3<double>(std::cos(asdf),  0, std::sin(asdf),
    //     //                                     0,               1, 0,
    //     //                                     -std::sin(asdf), 0, std::cos(asdf));

    //     // for (double i = 0; i < 2 * M_PI; i+=M_PI_4 / 8.0) {
    //     //     double asdf = 0.0;
    //     //     // this rotates around the y axis
    //     //     vec3<double> rota = mat3x3<double>::rotate(O, vec3<double>::cross(inDirection, normal).normalize(), i);
            
    //     //     // mat3x3<double> rot = mat3x3<double>(std::cos(i), -std::sin(i), 0,
    //     //     //                                     std::sin(i),  std::cos(i), 0,
    //     //     //                                     0,             0,            1);
    //     //     std::cout << rota << std::endl;;
    //     // }

    //     // convert vector back into original rotation
    //     vec3<double> outDirection = R.inverse() * O;

    //     // std::cout << outDirection << std::endl;

    //     // return vector
    //     // std::cout << outDirection << std::endl;
    //     return outDirection;
    // }

    // void beckspizz::test() {
    //     // double rands[100000] = {};
    //     // for (int i = 0; i < 100000; i++)  {
    //     //     rands[i] = math::randRange<double>(0.0, 1.0);
    //     //     std::cout << rands[i] << std::endl;
    //     // }
    //     // std::cout << "----------------" << std::endl;
    //     // for (int i = 0; i < 100000; i++)  {
    //     //     // std::cout << randomSampleBeta(0.12) << std::endl;
    //     //     std::cout << randomSampleBeta(1.4) << std::endl;
    //     //     // std::cout << randomSampleBeta(0.9) << std::endl;
    //     // }
    //     // std::cout << maxBeta(1.4) << std::endl;
    //     // std::cout << maxBeta(0.9) << std::endl;

    //     // sampleBounceDirection(vec3<double>(0.5, -1.5, 1.0).normalize(), 
    //     //                       vec3<double>(0.0, 1.0, 0.0).normalize());
    //     // sampleBounceDirection(vec3<double>(1.0, -1.0, 1.0).normalize(), 
    //     //                       vec3<double>(0.0, 1.0, 0.0).normalize());

    //     // // azimuth testing
    //     // // first quad
    //     // sampleBounceDirection(vec3<double>(1.0, -1.0, -1.0).normalize(), 
    //     //                       vec3<double>(0.0, 1.0, 0.0).normalize());
    //     // // second quad
    //     // sampleBounceDirection(vec3<double>(-1.0, -1.0, -1.0).normalize(), 
    //     //                       vec3<double>(0.0, 1.0, 0.0).normalize());
    //     // // third quad
    //     // sampleBounceDirection(vec3<double>(-1.0, -1.0, 1.0).normalize(), 
    //     //                       vec3<double>(0.0, 1.0, 0.0).normalize());
    //     // // fourth quad
    //     // sampleBounceDirection(vec3<double>(1.0, -1.0, 1.0).normalize(), 
    //     //                       vec3<double>(0.0, 1.0, 0.0).normalize());

    //     // // elevation testing
    //     // // first quad
    //     // sampleBounceDirection(vec3<double>(1.0, -1.0, 0.0).normalize(), 
    //     //                       vec3<double>(0.0, 1.0, 0.0).normalize());
    //     // // second quad
    //     // sampleBounceDirection(vec3<double>(1.0, 1.0, 0.0).normalize(), 
    //     //                       vec3<double>(0.0, 1.0, 0.0).normalize());
    //     // // third quad
    //     // sampleBounceDirection(vec3<double>(-1.0, 1.0, 0.0).normalize(), 
    //     //                       vec3<double>(0.0, 1.0, 0.0).normalize());
    //     // // fourth quad
    //     // sampleBounceDirection(vec3<double>(-1.0, -1.0, 0.0).normalize(), 
    //     //                       vec3<double>(0.0, 1.0, 0.0).normalize());


    //     for (int i = 0; i < 100; i++) {
    //         // vec3<double> asdf = sampleBounceDirection(vec3<double>(-0.05, -1.0, -0.1).normalize(), 
    //         //                                           vec3<double>(0.0, 1.0, 0.0).normalize());
    //         vec3<double> asdf = sampleBounceDirection(vec3<double>(-0.5, -1.0, -1.0).normalize(), 
    //                                                   vec3<double>(0.0, 1.0, 0.0).normalize());
    //         std::cout << asdf << std::endl;
    //         // std::cout << asdf << std::endl;
    //     }
    //     // for (int i = 0; i < 100; i++) {
    //     //     vec3<double> asdf = sampleBounceDirection(vec3<double>(-1.5, -1.5, -1.0).normalize(), 
    //     //                                               vec3<double>(0.0, 1.0, 0.0).normalize());
    //     // }
    // }

    // double beckspizz::pdf(const double beta, const double phi) const {
    //     double tanBeta = std::tan(beta);
    //     double cosBeta = std::cos(beta);
    //     double cosPhi = std::cos(phi);
    //     double sinPhi = std::sin(phi);
    //     return (std::exp(-tanBeta * tanBeta * ((cosPhi * cosPhi * invAlphaXSqr) + (sinPhi * sinPhi * invAlphaYSqr))) * invDenomConst) / (cosBeta * cosBeta * cosBeta * cosBeta);
    // }
    
    // double beckspizz::maxProbPhi(const double phi) const {
    //     double cosPhi = std::cos(phi);
    //     double sinPhi = std::sin(phi);
    //     double max = std::acos((alphaX * alphaX * sinPhi * sinPhi + alphaY * alphaY * cosPhi * cosPhi) * invAlphaXSqr * invAlphaYSqr - 1.0) / 2.0;
    //     return max != max ? pdf(0.0, phi) : pdf(max, phi);
    // }

    // double beckspizz::maxProbBeta(const double beta) const {
    //     return math::max(pdf(beta, 0.0), pdf(beta, M_PI_2));
    // }

    // double beckspizz::randomSampleBeta(const double phi) const {
    //     double max = maxProbBeta(phi);
    //     double randX, randY;
    //     do {
    //         randX = math::randRange<double>(-M_PI_2, M_PI_2);
    //         randY = math::randRange<double>(0.0, max);
    //     } while (randY > pdf(randX, phi));
    //     return randX;
    // }

    // double beckspizz::randomSamplePhi(const double beta) const {
    //     double max = maxProbPhi(beta);
    //     double randX, randY;
    //     do {
    //         randX = math::randRange<double>(-M_PI_2, M_PI_2);
    //         randY = math::randRange<double>(0.0, max);
    //     } while (randY > pdf(beta, randX));
    //     return randX;
    // }
}
