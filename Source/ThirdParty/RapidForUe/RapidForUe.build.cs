// Copyright aXiuShen. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;
using System.Text;
using System.Collections.Generic;


public class RapidForUe : ModuleRules
{
    public RapidForUe(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        //PublicSystemIncludePaths.Add(ModuleDirectory);
        PublicIncludePaths.Add(ModuleDirectory);
    }
}
