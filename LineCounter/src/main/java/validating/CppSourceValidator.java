package validating;

public class CppSourceValidator extends SourceValidator
{
	@Override
	protected void addAllValidExtensions()
	{
		addExtension(".c");
		addExtension(".cpp");
		addExtension(".h");
		addExtension(".hpp");
	}
	
}
