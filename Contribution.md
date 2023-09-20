# Contribution

To reduce double-communication, we use GitHub's commit messages as our primary medium of communication
for real, tangible progress. By "tangible" we mean progress on code, documentation, etc. Obviously, there
are many other intangible forms of real progress, such as discussions and individual thoughts that end up
in resolutions to questions, issues and problems. The primary medium for those is our [Kaizen workspace in Slack](https://kaizencpp.slack.com).

## Tips

### Commits with descriptions
Git has this nice feature that allows you to specify a description to a commit message by specifying it in a second
`-m` message, for example:
> git commit -m "Use `std::empty()` instead of `std::size()`" -m "Intent is more explicit with std::empty()."

Which can also be done from an IDE like Visual Studio and Visual Studio Code by simply adding a new line after the
main commit message. GitHub will then pick it up and display as `...` that'll expand to show the detailed description:
![image](https://github.com/heinsaar/kaizen/assets/14178490/c8cdc002-7e67-4266-8c21-f6fc1dda7e23)
