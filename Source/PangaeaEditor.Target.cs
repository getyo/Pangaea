using UnrealBuildTool;

public class PangaeaEditorTarget : TargetRules
{
    public PangaeaEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.AddRange(new string[] { "Pangaea" });
    }
}