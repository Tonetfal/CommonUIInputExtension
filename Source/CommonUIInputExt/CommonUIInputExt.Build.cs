// Author: Antonio Sidenko (Tonetfal), April 2024

using UnrealBuildTool;

public class CommonUIInputExt : ModuleRules
{
    public CommonUIInputExt(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "CommonInput",
                "CommonUI",
                "Core",
                "EnhancedInput",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "GameplayTags",
            }
        );
    }
}