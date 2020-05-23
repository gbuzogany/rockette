# MacOS

## 1 - Install Xcode

[App Store link](https://apps.apple.com/app/xcode/id497799835)

## 2 - Install Bazel

[Bazel Installation Instructions](https://docs.bazel.build/versions/master/install-windows.html).

## 3 - Build the project

```
bazel build //rkt:rockette --cpu="darwin_x86_64"
```

## 4 - Run the project

```
bazel run //rkt:rockette --cpu="darwin_x86_64"
```
