import re
import sys

def extract_latest_version(changelog):
    """Extract the latest version from the CHANGELOG."""
    latest_version_match = re.search(r'## \[(\d+\.\d+\.\d+)\]', changelog)
    if not latest_version_match:
        raise ValueError("Could not find the latest version in CHANGELOG.md")
    return latest_version_match.group(1)

def extract_changelog_for_version(changelog, version):
    """Extract the changelog entries for the specified version."""
    version_pattern = r'## \[' + re.escape(version) + r'\](.*?)(?=\n## |\Z)'
    version_changes_match = re.search(version_pattern, changelog, re.S)
    
    if not version_changes_match:
        raise ValueError(f"Could not extract changelog for version {version}.")
    
    return version_changes_match.group(1).strip()

def split_version(version):
    """Splits the version into major, minor, and patch."""
    version_parts = version.split('.')
    if len(version_parts) != 3:
        raise ValueError("Invalid version format in CHANGELOG.md. Expected format: MAJOR.MINOR.PATCH")
    return version_parts

def update_readme(readme_in_path, readme_out_path, changelog_path):
    try:
        # Read the CHANGELOG.md file
        with open(changelog_path, 'r', encoding='utf-8') as changelog_file:
            changelog = changelog_file.read()

        # Extract the latest version and the corresponding changelog
        latest_version = extract_latest_version(changelog)
        changelog_for_version = extract_changelog_for_version(changelog, latest_version)
        major, minor, patch = split_version(latest_version)

        # Read the README.md.in file
        with open(readme_in_path, 'r', encoding='utf-8') as readme_in_file:
            readme = readme_in_file.read()

        # Replace placeholders in the README.md
        readme = readme.replace('@PROJECT_NAME@', 'mptf_core')
        readme = readme.replace('@PROJECT_VERSION@', latest_version)
        readme = readme.replace('@PROJECT_VERSION_MAJOR@', major)
        readme = readme.replace('@PROJECT_VERSION_MINOR@', minor)
        readme = readme.replace('@PROJECT_VERSION_PATCH@', patch)
        readme = readme.replace('## Changelog:\nInitial commit with complete project structure', f'## Changelog:\n{changelog_for_version}')

        # Write to README.md
        with open(readme_out_path, 'w', encoding='utf-8') as readme_out_file:
            readme_out_file.write(readme)

        print(f"README.md updated to version {latest_version}.")

    except FileNotFoundError as fnf_error:
        print(f"Error: File not found - {fnf_error}")
        sys.exit(1)
    
    except ValueError as ve:
        print(f"Error: {ve}")
        sys.exit(1)
    
    except Exception as e:
        print(f"Unexpected error while updating README.md: {e}")
        sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: update_readme.py <README.md.in> <README.md> <CHANGELOG.md>")
        sys.exit(1)
    
    update_readme(sys.argv[1], sys.argv[2], sys.argv[3])
