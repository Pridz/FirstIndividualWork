package line;

import interfaces.ILineCounter;

public abstract class LineCounter implements ILineCounter
{
	private LineCounterData data;
	private boolean isBlockCommentOpened = false;
	private String blockCommentStart;
	private String blockCommentEnd;
	private String lineCommentStart;

	protected LineCounter()
	{
		blockCommentStart = getBlockCommentStart();
		blockCommentEnd = getBlockCommentEnd();
		lineCommentStart = getLineCommentStart();
	}
	
	protected abstract String getBlockCommentStart();
	protected abstract String getBlockCommentEnd();
	protected abstract String getLineCommentStart();

	@Override
	public LineCounterData getData(String inputString)
	{
		data = new LineCounterData();
		
		for (String line : splitToLines(inputString))
			countLine(line);
			
		return data;
	}

	private String[] splitToLines(String inputString)
	{
		String[] allLines = inputString.split("\r\n");
		return allLines;
	}
	
	private void countLine(String line)
	{
		if(blockCommentStartedIn(line))
			isBlockCommentOpened = true;		
		
		addSuiteLineToData(line);			
		
		if(shouldCloseCommentBlock(line))
			isBlockCommentOpened = false;
	}

	private boolean blockCommentStartedIn(String line)
	{
		return line.contains(blockCommentStart);
	}

	private void addSuiteLineToData(String line)
	{
		if(isCommentedLine(line))
			data.commentedLines++;
		else if(isWhiteCharLine(line))
			data.emptyLines++;
		else
			data.sourceLines++;
	}

	private boolean isCommentedLine(String line)
	{
		return isBlockCommentOpened || line.contains(lineCommentStart);
	}

	private boolean isWhiteCharLine(String line)
	{
		return line.isEmpty() || (line.trim().length() == 0);
	}

	private boolean shouldCloseCommentBlock(String line)
	{
		return isBlockCommentOpened && blockCommentClosedIn(line);
	}

	private boolean blockCommentClosedIn(String line)
	{
		return line.contains(blockCommentEnd);
	}
}
