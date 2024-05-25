const std = @import("std");
const raylib = @import("raylib");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "main",
        .target = target,
        .optimize = optimize,
    });
    const raylib_lib = raylib.addRaylib(b, target, optimize, .{}) catch unreachable;

    exe.linkLibC();
    if (optimize == .Debug) {
        exe.addCSourceFiles(.{
            .files = &([_][]const u8{"main.c"}),
            .flags = &([_][]const u8{"-g"}),
        });
        const game_lib = b.addSharedLibrary(.{
            .optimize = optimize,
            .target = target,
            .name = "plug",
        });
        game_lib.addCSourceFiles(.{
            .files = &([_][]const u8{ "game_main.c", "level.c" }),
            .flags = &([_][]const u8{ "-g", "-fPIC", "-I./include" }),
        });
        game_lib.linkLibrary(raylib_lib);
        b.installArtifact(game_lib);
    } else {
        exe.addCSourceFiles(.{
            .files = &([_][]const u8{ "game_main.c", "level.c" }),
            .flags = &([_][]const u8{"-I./include/"}),
        });
        exe.linkLibrary(raylib_lib);
    }
    b.installFile("lvl_one.png", "./levels/lvl_one.png");
    b.installArtifact(exe);

    const run_exe = b.addRunArtifact(exe);
    const run_step = b.step("run", "Run the game");
    run_step.dependOn(&run_exe.step);
}
