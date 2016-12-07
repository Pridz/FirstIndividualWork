package interfaces;

import java.io.File;

public interface IFileResolver
{
	public String getContent(File file);
	public String[] getContent(File[] files);
}
