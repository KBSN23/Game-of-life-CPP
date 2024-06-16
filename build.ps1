$csfmlLibPath = "SFML\lib\gcc"
$csfmlIncludePath = "SFML\include"
$sourcePath = "src"
$outPath = "out"

$sourceFiles = Get-ChildItem -Path "$sourcePath" -Filter *.cpp

$sourceFilesList = @()

foreach ($file in $sourceFiles) {
    $sourceFilesList += $file.FullName
}

$gccCommand = "g++ -Wall -O2 -L$csfmlLibPath -I$csfmlIncludePath"

foreach ($sourceFile in $sourceFilesList) {
    $gccCommand += " '$sourceFile' "
}

$gccCommand += " -lcsfml-graphics -lcsfml-window -lcsfml-system -o $outPath\program"

Invoke-Expression $gccCommand
