# Install built RME fork for Alastoria (per-user, no admin).
$ErrorActionPreference = 'Stop'
$repoRoot = Split-Path -Parent $PSScriptRoot
$otRoot = Split-Path -Parent $repoRoot

$candidates = @(
	Join-Path $repoRoot 'build\Release\rme.exe',
	Join-Path $repoRoot 'build\source\Release\rme.exe',
	Join-Path $repoRoot 'build\rme.exe'
)
$built = $candidates | Where-Object { Test-Path -LiteralPath $_ } | Select-Object -First 1
if (-not $built) {
	throw "rme.exe not found. Build first: powershell -File rme/scripts/build-windows.ps1"
}

$destDir = Join-Path $env:LOCALAPPDATA 'AlastoriaRME'
if (-not (Test-Path -LiteralPath $destDir)) {
	New-Item -ItemType Directory -Path $destDir -Force | Out-Null
}
$destExe = Join-Path $destDir 'rme.exe'
Copy-Item -LiteralPath $built -Destination $destExe -Force

$dataDir = Join-Path $otRoot 'Map\rme\data\1098'
if (-not (Test-Path -LiteralPath $dataDir)) {
	throw "Missing RME data: $dataDir"
}

$regPath = 'HKCU:\Software\Remere\'s Map Editor'
if (-not (Test-Path -LiteralPath $regPath)) {
	New-Item -Path $regPath -Force | Out-Null
}
New-ItemProperty -Path $regPath -Name 'data_directory' -Value $dataDir -PropertyType String -Force | Out-Null

Write-Host "Installed: $destExe"
Write-Host "Data dir:  $dataDir"
Write-Host 'Run install-creatures.ps1 if creature list changed.'
