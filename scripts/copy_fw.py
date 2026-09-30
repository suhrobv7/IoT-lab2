# scripts/copy_fw.py
Import("env")
import os, shutil

ROOT = ".pio"
OUT = os.path.join(ROOT, "build", "wokwi")
os.makedirs(OUT, exist_ok=True)


def _copy_to_wokwi(target, source, env):
    src = str(target[0])
    current_env = env.get("PIOENV", "default")

    env_dir = os.path.join(ROOT, "build", "wokwi", current_env)
    os.makedirs(env_dir, exist_ok=True)

    copied_name = os.path.basename(src)
    shutil.copy2(src, os.path.join(env_dir, copied_name))
    shutil.copy2(src, os.path.join(OUT, copied_name))

    print(f"[wokwi] copied {copied_name} for env={current_env}")


# Run after each build finishes so Wokwi always loads the latest firmware for
# the currently selected PlatformIO environment.
env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", _copy_to_wokwi)
env.AddPostAction("$BUILD_DIR/${PROGNAME}.elf", _copy_to_wokwi)
