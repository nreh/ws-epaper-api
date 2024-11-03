import importlib.util  # for making sure the user has required packages installed


def requirePackage(pkg: str, hint=None) -> bool:
    """
    Returns False if the user doesn't have the specified package installed. Also prints out a message indicating as such to
    the user.
    """
    if importlib.util.find_spec(pkg) is None:
        if hint == None:
            hint = f"try Googling {pkg}"
        else:
            hint = f"try installing it using pip install {hint}"
        print(
            f"Unable to find required package '{pkg}', {hint}")
        return False
    else:
        print(f"Found required package '{pkg}' ✔")
        return True


def requirePackages(pkgs: 'list[str]'):
    hasAllPackages = True
    for p in pkgs:
        if '|' in p:  # split install hint by |
            a = p.split('|')
            hasAllPackages = requirePackage(a[0], a[1]) and hasAllPackages
        else:
            hasAllPackages = requirePackage(p) and hasAllPackages

    if not hasAllPackages:
        exit(1)

    print("---\n")
