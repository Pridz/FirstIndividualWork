package line;

public class CppLineCounter extends LineCounter
{

	@Override
	protected String getBlockCommentStart()
	{
		return "/*";
	}

	@Override
	protected String getBlockCommentEnd()
	{
		return "*/";
	}

	@Override
	protected String getLineCommentStart()
	{
		return "//";
	}

}
