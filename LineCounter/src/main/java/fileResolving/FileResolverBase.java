package fileResolving;

import java.io.File;

import interfaces.IFileResolver;

public abstract class FileResolverBase implements IFileResolver
{
		
	public abstract String getContent(File file);

	@Override
	public String[] getContent(File[] files)
	{
		String[] allContent = new String[files.length];
		
		for(int i=0; i<files.length; i++)
			allContent[i] = getContent(files[i]);
				
		return allContent;
	}
	
}
