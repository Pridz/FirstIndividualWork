package line;

import static org.junit.Assert.*;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import org.junit.Before;
import org.junit.Test;

import fileResolving.DefaultFileResolver;
import interfaces.IFileResolver;
import interfaces.ILineCounter;
import interfaces.ISourceValidator;
import navigating.FileManager;
import validating.CppSourceValidator;

public class LineCounterTest
{
	ILineCounter counter = new CppLineCounter();
	private IFileResolver resolver;
	private FileManager manager;
	private ISourceValidator sourceValidator;
	private LineCounterData wholeResult;
	
	@Before
	public void setUp()
	{
		resolver = new DefaultFileResolver();
		manager = new FileManager();
		sourceValidator = new CppSourceValidator();
		wholeResult = new LineCounterData();
	}
	
	@Test
	public void lineCounting_someRandomCppSources()
	{
		List<String> inputData = prepareValidFileDataForLineCalculator();
		
		for (String inputString : inputData)
			wholeResult = wholeResult.add(counter.getData(inputString));

		assertEquals(891, wholeResult.sourceLines);
		assertEquals(178, wholeResult.emptyLines);
		assertEquals(16, wholeResult.commentedLines);
	}
	
	private List<String> prepareValidFileDataForLineCalculator()
	{
		String testedPath = "src/test/resources";
		List<File> validFiles = manager.getFiles(testedPath);
			
		List<String> result = new ArrayList<>();
		for (File file : validFiles)
			if(sourceValidator.isPathASourceFile(file.getName()))
				result.add(resolver.getContent(file));
		
		return result;
	}
}
