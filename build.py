#!/usr/bin/env python3

from argparse import ArgumentParser
import os
import shutil
import subprocess
import sys
import logging

## Logging logic.
stream_handler = logging.StreamHandler()
formatter = logging.Formatter("[%(levelname)s] %(message)s")
stream_handler.setFormatter(formatter)
logger = logging.getLogger("build")
logger.addHandler(stream_handler)
logger.setLevel(logging.INFO)


def run_tests(test_suite_sections: list[str]):
    if len(test_suite_sections) == 1 and "all" in test_suite_sections:
        raise RuntimeError("Only `all` mode is supported for `--run-tests` currently")


def build_grace(args):
    if args.run_tests:
        # TODO (vinayakdsci): Implement test runs when the test-suite is wired up.
        raise NotImplementedError("Unsupported: test-suite runs are not supported yet")

    logger.info("Starting build...")
    bzl_cmd = None
    try:
        bzl_cmd = find_bzl_binary()
    except Exception as e:
        logger.error(e.__str__())
        raise

    # Invoke a subprocess running bazelisk.
    logger.info("Invoking bazelisk...")
    process = subprocess.run(
        ["bazelisk", "build", ":grc"],
        capture_output=True,
    )

    try:
        process.check_returncode()
    except:
        logger.error(
            f"Process return with exit-code {process.returncode}. {process.stderr.decode()}"
        )
        raise

    assert os.path.exists(os.path.join("bazel-bin", "grc"))
    logger.info(f"SUCCESS. Build succeeded with exit-code {process.returncode}")


def find_bzl_binary():
    bzl_cmd = shutil.which("bazelisk")
    if not bzl_cmd:
        raise FileNotFoundError("Could not find `bazelisk` binary in PATH")

    return bzl_cmd


if __name__ == "__main__":
    parser = ArgumentParser(
        prog="build",
        description="Build utility for Grace source code",
        epilog="Default behavior is to build only the `grc` binary. To run tests, pass `--run-tests`.",
    )
    parser.add_argument(
        "--run-tests",
        type=str,
        # nargs="+",
        choices=["all"],
    )

    try:
        build_grace(parser.parse_args())
    except Exception as e:
        logger.error(e.__str__())
