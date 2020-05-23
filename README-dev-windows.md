# Windows

## 1 - Install bazel

### 1.1 - Manual installation

[Bazel Installation Instructions](https://docs.bazel.build/versions/master/install-windows.html).


### 1.2 - An easy way, use Chocolatey

First, install chocolatey. From an elevated powershell, run:

```
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
```

Then install bazel:

```
choco install bazel
```

## 2 - Install MSYS2

```
https://www.msys2.org
```

## 2 - Install Visual Studio Community

```
https://visualstudio.microsoft.com/vs/community/
```

Make sure you install the `Desktop development with C++` package.

## 3 - Building the project

From a command prompt, go to the project directory, and run:

```
bazel build //rkt:rockette
```

It should download all the dependencies automatically.

## 4 - Running the project

There's just one more step that's needed to run the project on Windows. The program expects to find all assets (shaders, textures, fonts, etc) in a directory called "rkt" in the CWD (current working directory, the directory where the project is running from).
For it to work with `bazel run`, you should copy the `{PROJECT_DIR}/rkt/etc` directory to `{PROJECT_DIR}/bazel-bin/rkt/rockette.exe.runfiles/rkt/`.

Then, run:

```
bazel run //rkt:rockette
```

To run the project.