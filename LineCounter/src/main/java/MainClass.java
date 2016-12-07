import java.io.File;
import java.util.List;

import fileResolving.DefaultFileResolver;
import interfaces.IFileResolver;
import interfaces.ILineCounter;
import line.CppLineCounter;
import line.LineCounterData;
import navigating.FileManager;
import validating.CppSourceValidator;
import validating.SourceValidator;

public class MainClass
{
	private static SourceValidator sourceValidator = new CppSourceValidator();
	private static IFileResolver fileConverter = new DefaultFileResolver();
	private static ILineCounter lineCounter = new CppLineCounter();
	private static FileManager filesManager = new FileManager();
	
	public static void main(String[] args)
	{
		if(args.length > 0)
			countAndPrintLines(args[0]);
		else
			countAndPrintLinesFromCurrentDirectory();
	}
	
	private static void countAndPrintLinesFromCurrentDirectory()
	{
		countAndPrintLines(filesManager.getFilesFromWorkingDirectory());
	}

	public static void countAndPrintLines(String sourceFolderPath)
	{
		countAndPrintLines(filesManager.getFiles(sourceFolderPath));
	}

	private static void countAndPrintLines(List<File> files)
	{
		LineCounterData result = countLines(files);
		printResult(result);
	}


	private static LineCounterData countLines(List<File> files)
	{
		LineCounterData result = new LineCounterData();
		
		files.removeIf((file) -> !sourceValidator.isPathASourceFile(file.getName()));
		for (File file : files)
			result = result.add(countLines(file));
			
		return result;
	}

	private static LineCounterData countLines(File file)
	{
		String wholeFileData = fileConverter.getContent(file);
		return lineCounter.getData(wholeFileData);
	}
	
	private static void printResult(LineCounterData result)
	{
		System.out.println("Source lines: " + result.sourceLines);
		System.out.println("Commented lines: " + result.commentedLines);
		System.out.println("Empty lines: " + result.emptyLines);
		System.out.println("Total: " + result.getTotalLines() + " lines");
	}

}




