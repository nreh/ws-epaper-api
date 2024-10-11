import importlib.util  # for making sure the user has required packages installed


def requirePackage(pkg: str) -> bool:
    """
    Returns False if the user doesn't have the specified package installed. Also prints out a message indicating as such to
    the user.
    """
    if importlib.util.find_spec(pkg) is None:
        print(
            f"Unable to find required package '{pkg}', Try installing it using 'pip install {pkg}")
        return False
    else:
        print(f"Found required package '{pkg}' ✔")
        return True


def requirePackages(pkgs: 'list[str]'):
    hasAllPackages = True
    for p in pkgs:
        hasAllPackages = requirePackage(p) and hasAllPackages

    if not hasAllPackages:
        exit(1)

    print("---\n")
