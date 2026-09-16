# Build Alastoria RME fork (Windows).
$ErrorActionPreference = 'Stop'
$repoRoot = Split-Path -Parent $PSScriptRoot
$buildDir = Join-Path $repoRoot 'build'

if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
	throw 'cmake not found. Install CMake and wxWidgets/Boost (see README-ALASTORIA.md).'
}

if (-not (Test-Path -LiteralPath $buildDir)) {
	New-Item -ItemType Directory -Path $buildDir | Out-Null
}

Push-Location $buildDir
try {
	cmake .. -DCMAKE_BUILD_TYPE=Release
	if ($LASTEXITCODE -ne 0) { throw 'cmake configure failed' }
	cmake --build . --config Release
	if ($LASTEXITCODE -ne 0) { throw 'cmake build failed' }
	Write-Host "Build OK. Look for rme.exe under: $buildDir"
} finally {
	Pop-Location
}
