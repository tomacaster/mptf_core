import re
import sys

def extract_latest_version(changelog):
    """Extract the latest version from the CHANGELOG."""
    latest_version_match = re.search(r'## \[(\d+\.\d+\.\d+)\]', changelog)
    if not latest_version_match:
        raise ValueError("Could not find the latest version in CHANGELOG.md")
    return latest_version_match.group(1)

def generate_changelog(changelog_path, changelog_out_path):
    """Generate the changelog dynamically."""
    try:
        # Read the existing changelog
        with open(changelog_path, 'r', encoding='utf-8') as changelog_file:
            changelog = changelog_file.read()

        # Write the changelog to the output file
        with open(changelog_out_path, 'w', encoding='utf-8') as changelog_out_file:
            changelog_out_file.write(changelog)

        print(f"CHANGELOG.md has been successfully generated.")

    except FileNotFoundError as fnf_error:
        print(f"Error: Changelog source file not found - {fnf_error}")
        sys.exit(1)

    except Exception as e:
        print(f"Unexpected error while generating CHANGELOG.md: {e}")
        sys.exit(1)

def update_readme(readme_in_path, readme_out_path):
    try:
        # Read the README.md.in file
        with open(readme_in_path, 'r', encoding='utf-8') as readme_in_file:
            readme = readme_in_file.read()

        # Replace placeholders in the README.md
        readme = readme.replace('@PROJECT_NAME@', 'mptf_core')
        readme = readme.replace('@PROJECT_VERSION@', '0.0.2')

        # Write to README.md
        with open(readme_out_path, 'w', encoding='utf-8') as readme_out_file:
            readme_out_file.write(readme)

        print(f"README.md updated successfully.")

    except FileNotFoundError as fnf_error:
        print(f"Error: README source file not found - {fnf_error}")
        sys.exit(1)

    except Exception as e:
        print(f"Unexpected error while updating README.md: {e}")
        sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: update_readme.py <README.md.in> <README.md> <CHANGELOG.md>")
        sys.exit(1)
    
    # Generate the changelog
    generate_changelog(sys.argv[3], sys.argv[3])

    # Update the README
    update_readme(sys.argv[1], sys.argv[2])
