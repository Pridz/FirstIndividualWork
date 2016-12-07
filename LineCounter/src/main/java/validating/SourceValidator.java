package validating;

import java.util.ArrayList;
import java.util.List;

import interfaces.ISourceValidator;

public abstract class SourceValidator implements ISourceValidator
{
	private List<String> validExtensions = new ArrayList<>();

	protected SourceValidator()
	{
		addAllValidExtensions();
	}
	
	protected abstract void addAllValidExtensions();
	
	@Override
	public boolean isPathASourceFile(String path)
	{	
		for (String extension : validExtensions)
			if(path.contains(extension))
				return true;
		return false;
	}
	
	protected void addExtension(String extension) throws InvalidExtensionException
	{
		if(invalidExtension(extension))
			throw new InvalidExtensionException();
		validExtensions.add(extension);
	}
	
	private boolean invalidExtension(String extension)
	{
		return !(extension.startsWith(".")) || extension.length() < 2;
	}

	class InvalidExtensionException extends RuntimeException
	{}
}
