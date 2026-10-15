
from pathlib import Path
import tempfile
import re
import sys
import subprocess

LIBRARY_DIR = Path(__file__).resolve().parent
expanded = set()
include_pattern = re.compile(r'^\s*#\s*include\s*"([^"]+)"\s*$')


def expand_file(path: Path) -> str:
    path = path.resolve()

    if path in expanded:
        return f"// Already included: {path.name}\n"

    expanded.add(path)
    result = []

    for line in path.read_text(encoding="utf-8-sig").splitlines():
        if re.match(r"^\s*#\s*pragma\s+once\b", line):
            continue

        match = include_pattern.match(line)

        if match:
            name = match.group(1)
            candidates = [path.parent / name, LIBRARY_DIR / name]
            header = next((p for p in candidates if p.is_file()), None)

            if header is not None:
                result.append(f"\n// BEGIN: {header.name}\n")
                result.append(expand_file(header))
                result.append(f"\n// END: {header.name}\n")
                continue

        result.append(line + "\n")

    return "".join(result)


def main():
    if len(sys.argv) != 2:
        print("Usage: python expand.py input.cpp")
        sys.exit(1)

    source = Path(sys.argv[1]).resolve()

    if not source.is_file():
        print(f"Input file not found: {source}")
        sys.exit(1)

    code = expand_file(source)

    # UTF-8の一時ファイルに展開結果を書き込む
    with tempfile.NamedTemporaryFile(
        mode="w",
        encoding="utf-8",
        newline="",
        suffix=".txt",
        delete=False
    ) as f:
        f.write(code)
        temp_path = Path(f.name)

    try:
        # WSLのパスをWindowsのパスに変換
        win_path = subprocess.check_output(
            ["wslpath", "-w", str(temp_path)],
            text=True
        ).strip()

        # PowerShellでUTF-8として読み込み、クリップボードへコピー
        ps_command = (
            f"$text = Get-Content -LiteralPath '{win_path}' "
            "-Raw -Encoding UTF8; Set-Clipboard -Value $text"
        )

        subprocess.run(
            ["powershell.exe", "-NoProfile", "-Command", ps_command],
            check=True
        )

        print("success!")

    finally:
        temp_path.unlink(missing_ok=True)

if __name__ == "__main__":
    main()
