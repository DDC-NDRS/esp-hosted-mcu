# Append idf5.5_py3.11_env path before run the script
$env:Path = 'C:\toolchain\esp\idf_tools\python_env\idf5.5_py3.11_env\Scripts;' + $env:Path

# Define the path to the script
$script_path = 'C:\toolchain\esp\esp-idf\5.5\export.ps1'

# Navigate to the script's directory to ensure $PSScriptRoot remains correct
Push-Location 'C:\toolchain\esp\esp-idf\5.5\'

# Execute the script
& $script_path

# Return to the original directory after executing the script
Pop-Location

$board_name = "weact_esp32-c6-a-n8"

# Create Junction (if there is RAMDISK on T:\)
# New-Item -ItemType Junction -Path "build" -Target "T:\esp-idf_build\$board_name\"
if ((Test-Path -Path "T:\") -and (-not (Test-Path -Path "T:\esp-idf_build\$board_name\"))) {
    New-Item -ItemType "directory" -Path "T:\esp-idf_build\$board_name\"
    New-Item -ItemType Junction -Path "build" -Target "T:\esp-idf_build\$board_name\"
}
