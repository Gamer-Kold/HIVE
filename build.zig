const std = @import("std");

pub fn build(b: *std.build.Builder) void {
    const target = b.standardTargetOptions(.{});

    const mode = b.standardReleaseOptions();

    const exe = b.addExecutable("HIVE", null);
    const flags = &[_][]const u8{};

    exe.setTarget(target);
    exe.setBuildMode(mode);
    exe.addCSourceFile("main.c", flags);
    exe.addIncludePath("include");
    exe.addLibraryPath("lib");
    exe.linkSystemLibrary("raylib");
    exe.linkLibC();
    exe.install();

    const run_step = std.build.RunStep.create(exe.builder, "run fresh");
    run_step.addArtifactArg(exe);

    const step = b.step("run", "Runs the executable");
    step.dependOn(&run_step.step);
}
