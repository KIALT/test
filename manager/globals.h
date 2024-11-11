#pragma once

#include "env_conf.h"
#include "settings.h"

class Globals
{
public:
    static Settings settings_;
    static EnvConf  env_conf_;
};
