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


def _error(e):
    logger.error(e.__str__())


def run_tests(test_suite_sections: list[str]):

    if "all" in test_suite_sections:
        # Keep adding more test sections here as the suite grows.
        test_suite_sections = ["lexer"]

    logger.info(f"Running tests for sections {test_suite_sections}")

    for section in test_suite_sections:
        process = subprocess.run(
            [
                "bazelisk",
                "test",
                f"//tests/{section}:grace_{section}_tests",
                "--cache_test_results=no",
            ],
            capture_output=True,
        )

        try:
            process.check_returncode()
            logger.info(f"{process.stdout.decode()}")
            logger.info(
                f"SUCCESS: Command [{' '.join(process.args)}] succeeded with exit-code {process.returncode}"
            )
        except:
            logger.error(
                f"Test run for section `{section}` failed with exit-code {process.returncode}\n{process.stderr.decode()}"
            )


def build_grace(args):
    logger.info("Starting build...")
    logger.info(f"ARGS: {args}")
    bzl_cmd = None
    try:
        bzl_cmd = find_bzl_binary()
    except Exception as e:
        _error(e)
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
            f"Process failed with exit-code {process.returncode}\n{process.stderr.decode()}"
        )
        raise

    assert os.path.exists(os.path.join("bazel-bin", "grc"))
    logger.info(
        f"SUCCESS: Command [{' '.join(process.args)}] succeeded with exit-code {process.returncode}"
    )

    if isinstance(args.run_tests, list):
        if len(args.run_tests) == 0:
            args.run_tests = ["all"]
        try:
            run_tests(args.run_tests)
            return
        except Exception as e:
            _error(e)


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
        nargs="*",
        default="",
        choices=["all"],
    )

    try:
        build_grace(parser.parse_args())
    except Exception as e:
        _error(e)
