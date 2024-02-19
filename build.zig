const std = @import("std");

const Build = std.Build;

pub fn build(b: *Build) void {
    const target = Build.standardTargetOptions(b, .{});
    const optimize = Build.standardOptimizeOption(b, .{});

    const game = b.addExecutable(.{
        .name = "game",
        .target = target,
        .optimize = optimize
    });
    game.linkLibCpp();
    game.addCSourceFile(.{.file = .{.path = "src/main.cpp"}});

    b.installArtifact(game);

    const run_game = b.addRunArtifact(game);
    const run_game_step = b.step("run-game", "Run the game.");
    run_game_step.dependOn(&run_game.step);
}