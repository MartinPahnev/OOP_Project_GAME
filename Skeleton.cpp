#include "Skeleton.h"

Skeleton::Skeleton() : UndeadUnit(SKELETONHEALTH, SKELETONHEALTH, SKELETONATTACKDAMAGE,
    SKELETONARMOUR, SKELETONARMOURTYPE, SKELETONFACTION, SKELETONUNITTYPE)
{}

std::string Skeleton::getName() const
{
    return std::string("Skeleton");
}
