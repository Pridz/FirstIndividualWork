package navigating;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class FileManager
{
	private static final String userDirectoryPropertyName = "user.dir";

	public List<File> getFilesFromWorkingDirectory()
	{
		File directory = new File(getWorkingDirectrory());
		return getAllFilesFromParentDirectory(directory);
	}
	
	private List<File> getAllFilesFromParentDirectory(File directory)
	{
		List<File> allFiles = new ArrayList<>();
		File[] items = directory.listFiles();
		
		for (File item : items)
			addAppropriateFiles(allFiles, item);
		
		return allFiles;
	}


	private void addAppropriateFiles(List<File> allFiles, File item)
	{
		if(item.isDirectory())
			allFiles.addAll(getAllFilesFromParentDirectory(item));
		else
			allFiles.add(item);
	}

	public List<File> getFiles(String directoryToWorkOn)
	{
		File directory = new File(directoryToWorkOn);
		return getAllFilesFromParentDirectory(directory);
	}

	private String getWorkingDirectrory()
	{
		return System.getProperty(userDirectoryPropertyName);
	}
	

}
