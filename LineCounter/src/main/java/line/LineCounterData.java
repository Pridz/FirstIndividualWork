package line;

public class LineCounterData
{
	public int commentedLines = 0;
	public int sourceLines = 0;
	public int emptyLines = 0;
	
	public LineCounterData add(LineCounterData toAdd)
	{
		LineCounterData result = new LineCounterData();
		result.commentedLines = toAdd.commentedLines + this.commentedLines;
		result.sourceLines = toAdd.sourceLines + this.sourceLines;
		result.emptyLines = toAdd.emptyLines + this.emptyLines;
		return result; 
	}
	
	public int getTotalLines()
	{
		return commentedLines + sourceLines + emptyLines;
	}
	
}
