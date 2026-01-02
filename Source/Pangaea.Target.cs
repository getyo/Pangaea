using UnrealBuildTool;

public class PangaeaTarget : TargetRules
{
    public PangaeaTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.AddRange(new string[] { "Pangaea" });
    }
}